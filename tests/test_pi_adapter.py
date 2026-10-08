"""Offline contract test: real pi and compiler, fake OpenAI-compatible server."""
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
from pathlib import Path
import shutil
import tempfile
import threading
import unittest

from bench import ROOT, run_one

@unittest.skipUnless(shutil.which("pi") and shutil.which("clang"), "pi and clang required")
class PiAdapter(unittest.TestCase):
    def test_sampling_tools_usage_and_failed_solution(self):
        requests = []
        class Handler(BaseHTTPRequestHandler):
            def log_message(self, *args):
                pass

            def do_POST(self):
                request = json.loads(self.rfile.read(int(self.headers["Content-Length"])))
                requests.append(request)
                if len(requests) == 1:
                    delta = {"role": "assistant", "tool_calls": [{
                        "index": 0, "id": "call_submit", "type": "function",
                        "function": {"name": "submit_source", "arguments": json.dumps({
                            "source": '#include <stdio.h>\nint main(void){puts("0");}'
                        })}}]}
                    finish = "tool_calls"
                else:
                    delta = {"role": "assistant", "content": "Done."}
                    finish = "stop"
                chunk = {"id": "fake", "object": "chat.completion.chunk",
                         "created": 0, "model": "fake"}
                stream = [
                    {**chunk, "choices": [{"index": 0, "delta": delta, "finish_reason": None}]},
                    {**chunk, "choices": [{"index": 0, "delta": {}, "finish_reason": finish}],
                     "usage": {"prompt_tokens": 10, "completion_tokens": 7, "total_tokens": 17}},
                ]
                body = "".join("data: " + json.dumps(c) + "\n\n" for c in stream) + "data: [DONE]\n\n"
                self.send_response(200)
                self.send_header("Content-Type", "text/event-stream")
                self.send_header("Content-Length", str(len(body.encode())))
                self.end_headers()
                self.wfile.write(body.encode())

        server = ThreadingHTTPServer(("127.0.0.1", 0), Handler)
        thread = threading.Thread(target=server.serve_forever, daemon=True)
        thread.start()
        try:
            config = json.loads((ROOT / "config.json").read_text())
            config.update(model="fake", ollama_url=f"http://127.0.0.1:{server.server_port}",
                          max_seconds=30)
            with tempfile.TemporaryDirectory() as d:
                result = run_one(Path(d), config, {
                    "language": "c", "task": "merge_intervals", "repeat": 0, "sampling_seed": 123
                }, 0)
            self.assertEqual(len(requests), 2)
            first = requests[0]
            self.assertEqual(first["seed"], 123)
            self.assertEqual(first["temperature"], .7)
            self.assertEqual(first["top_p"], .8)
            self.assertEqual(first["max_tokens"], 4096)
            self.assertEqual(first["reasoning_effort"], "none")
            self.assertEqual([t["function"]["name"] for t in first["tools"]], ["submit_source"])
            self.assertEqual(result["tokens"]["output"], 14)
            self.assertEqual(result["submissions"], 1)
            self.assertFalse(result["infrastructure_error"])
            self.assertFalse(result["success"])
            self.assertEqual(result["par2_seconds"], 60)
        finally:
            server.shutdown()
            server.server_close()
            thread.join()

if __name__ == "__main__":
    unittest.main()

"""Offline contracts: real pi and compiler, fake local inference (no Ollama calls)."""
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
from pathlib import Path
import shutil
import tempfile
import threading
import unittest

from bench import ROOT, run_one

BAD = '#include <stdio.h>\nint main(void){puts("0");}'
OVERFIT = '#include <stdio.h>\nint main(void){int n;scanf("%d",&n);if(n==3)puts("2\\n1 4\\n7 9");else if(n==0)puts("0");else puts("2\\n1 2\\n3 4");}'
CORRECT = """
#include <stdio.h>
#include <stdlib.h>
typedef struct {long long l,r;} Interval;
int cmp(const void *a,const void *b){
 const Interval *x=a,*y=b;
 return (x->l>y->l)-(x->l<y->l);
}
int main(void){
 int n; Interval a[200],out[200];
 if(scanf("%d",&n)!=1)return 1;
 for(int i=0;i<n;i++)scanf("%lld%lld",&a[i].l,&a[i].r);
 qsort(a,n,sizeof(Interval),cmp);
 int k=0;
 for(int i=0;i<n;i++){
  if(k && a[i].l<=out[k-1].r){
   if(a[i].r>out[k-1].r)out[k-1].r=a[i].r;
  }else out[k++]=a[i];
 }
 printf("%d\\n",k);
 for(int i=0;i<k;i++)printf("%lld %lld\\n",out[i].l,out[i].r);
 return 0;
}
""".replace("\\\\n", "\\n")

@unittest.skipUnless(shutil.which("pi") and shutil.which("clang"), "pi and clang required")
class PiAdapter(unittest.TestCase):
    def run_script(self, responses, **overrides):
        requests = []
        class Handler(BaseHTTPRequestHandler):
            def log_message(self, *args):
                pass

            def do_POST(self):
                request = json.loads(self.rfile.read(int(self.headers["Content-Length"])))
                requests.append(request)
                sources = responses[len(requests)-1] if len(requests)<=len(responses) else None
                if sources:
                    delta = {"role":"assistant", "tool_calls":[
                        {"index":i, "id":f"call_{len(requests)}_{i}", "type":"function",
                         "function":{"name":"submit_source","arguments":json.dumps({"source":source})}}
                        for i,source in enumerate(sources)]}
                    finish = "tool_calls"
                else:
                    delta, finish = {"role":"assistant","content":"Done."}, "stop"
                chunk = {"id":"fake","object":"chat.completion.chunk","created":0,"model":"fake"}
                stream = [
                    {**chunk,"choices":[{"index":0,"delta":delta,"finish_reason":None}]},
                    {**chunk,"choices":[{"index":0,"delta":{},"finish_reason":finish}],
                     "usage":{"prompt_tokens":10,"completion_tokens":7,"total_tokens":17}},
                ]
                body = "".join("data: "+json.dumps(c)+"\n\n" for c in stream)+"data: [DONE]\n\n"
                self.send_response(200)
                self.send_header("Content-Type","text/event-stream")
                self.send_header("Content-Length",str(len(body.encode())))
                self.end_headers()
                self.wfile.write(body.encode())

        server = ThreadingHTTPServer(("127.0.0.1",0),Handler)
        thread = threading.Thread(target=server.serve_forever,daemon=True)
        thread.start()
        try:
            config = json.loads((ROOT/"config.json").read_text())
            config.update(model="fake",ollama_url=f"http://127.0.0.1:{server.server_port}",
                          max_seconds=30,max_turns=2)
            config.update(overrides)
            with tempfile.TemporaryDirectory() as d:
                result = run_one(Path(d),config,{
                    "language":"c","task":"merge_intervals","repeat":0,"sampling_seed":123
                },0)
                work=next(Path(d).glob("*/work"))
                source=(work/"main.c").read_text() if (work/"main.c").exists() else None
            return result,requests,source
        finally:
            server.shutdown(); server.server_close(); thread.join()

    def test_sampling_tools_usage_and_failed_solution(self):
        result,requests,_ = self.run_script([[BAD],None])
        self.assertEqual(len(requests),2)
        first=requests[0]
        for name,value in {"seed":123,"temperature":.7,"top_p":.8,"max_tokens":2048,
                           "reasoning_effort":"none"}.items():
            self.assertEqual(first[name],value)
        self.assertEqual([t["function"]["name"] for t in first["tools"]],["submit_source"])
        self.assertEqual(result["tokens"]["output"],14)
        self.assertEqual(result["submissions"],1)
        self.assertFalse(result["infrastructure_error"])
        self.assertEqual(result["stop"],"completed")
        self.assertFalse(result["success"])
        self.assertEqual(result["par2_seconds"],60)

    def test_public_pass_stops_and_freezes_source_even_with_multiple_calls(self):
        result,requests,source = self.run_script([[CORRECT,BAD],[BAD]])
        self.assertEqual(result["stop"],"public_pass")
        self.assertEqual(len(requests),1)
        self.assertEqual(result["submissions"],1)
        self.assertEqual(source,CORRECT)
        self.assertTrue(result["success"],result)
        self.assertTrue(result["usage_complete"])
        self.assertEqual(result["tokens"]["output"],7)

    def test_public_pass_can_still_fail_hidden_tests(self):
        result,requests,_ = self.run_script([[OVERFIT],[CORRECT]])
        self.assertEqual(result["stop"],"public_pass")
        self.assertEqual(len(requests),1)
        self.assertFalse(result["success"])
        self.assertFalse(result["hidden"]["passed"])

    def test_submission_limit_does_not_request_another_completion(self):
        result,requests,_ = self.run_script([[BAD],[CORRECT]],max_submissions=1)
        self.assertEqual(result["stop"],"submission_budget")
        self.assertEqual(len(requests),1)
        self.assertFalse(result["success"])
        self.assertFalse(result["infrastructure_error"])
        self.assertEqual(result["tokens"]["output"],7)

    def test_success_on_last_submission_counts(self):
        result,requests,_ = self.run_script([[BAD],[CORRECT]],max_submissions=2)
        self.assertEqual(len(requests),2)
        self.assertEqual(result["stop"],"public_pass")
        self.assertTrue(result["success"],result)
        self.assertEqual(result["tokens"]["output"],14)

if __name__ == "__main__":
    unittest.main()

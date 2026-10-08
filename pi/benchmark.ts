import { Type } from "@earendil-works/pi-ai";
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { writeFileSync, appendFileSync, mkdirSync } from "node:fs";
import { join } from "node:path";

export default function (pi: ExtensionAPI) {
  let attempts = 0;
  let busy = false;
  let closed = "";
  const work = process.env.BENCH_WORK!;
  const root = process.env.BENCH_ROOT!;
  const lang = process.env.BENCH_LANGUAGE!;
  const max = Number(process.env.BENCH_ATTEMPTS!);
  pi.on("turn_end", (_event, ctx) => {
    // Prevent a new inference request even before the parent consumes the stop event.
    if (closed) ctx.abort();
  });
  pi.registerTool({
    name: "submit_source",
    label: "Submit source",
    description: "Save a complete replacement source file, compile it, and run the public examples. Returns compiler errors or test feedback. On success, finish; do not resubmit.",
    parameters: Type.Object({ source: Type.String({ description: "Complete source code, without Markdown fences" }) }),
    async execute(_id, params, signal) {
      if (closed) throw new Error("Trial already closed: " + closed);
      if (busy) throw new Error("Submit one source at a time.");
      if (attempts >= max) throw new Error("Submission budget exhausted.");
      busy = true;
      try {
        attempts++;
        const filename = lang === "c" ? "main.c" : "main.go";
        mkdirSync(join(work, "revisions"), { recursive: true });
        writeFileSync(join(work, filename), params.source);
        writeFileSync(join(work, "revisions", String(attempts) + "-" + filename), params.source);
        const result = await pi.exec(process.env.BENCH_PYTHON!, [
          join(root, "judge.py"), work, lang, process.env.BENCH_TASK!, "public"
        ], { signal, timeout: 120000 });
        if (result.code !== 0) throw new Error("Judge infrastructure error: " + result.stderr);
        const feedback = JSON.parse(result.stdout);
        closed = feedback.passed ? "public_pass" : attempts >= max ? "submission_budget" : "";
        const details = {attempt: attempts, ...feedback, controller_stop: closed || null};
        appendFileSync(join(work, "attempts.jsonl"), JSON.stringify(details) + "\n");
        return {content: [{type: "text", text: JSON.stringify({
          ...feedback, submissions_remaining: max - attempts
        })}], details};
      } finally {
        busy = false;
      }
    }
  });
}

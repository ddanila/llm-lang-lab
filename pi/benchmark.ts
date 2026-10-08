import { Type } from "@earendil-works/pi-ai";
import type { ExtensionAPI } from "@earendil-works/pi-coding-agent";
import { writeFileSync, appendFileSync, mkdirSync } from "node:fs";
import { join } from "node:path";

export default function (pi: ExtensionAPI) {
  let attempts = 0;
  const work = process.env.BENCH_WORK!;
  const root = process.env.BENCH_ROOT!;
  const lang = process.env.BENCH_LANGUAGE!;
  const max = Number(process.env.BENCH_ATTEMPTS!);
  pi.registerTool({
    name: "submit_source",
    label: "Submit source",
    description: "Save a complete replacement source file, compile it, and run the public examples. Returns compiler errors or test feedback. On success, finish; do not resubmit.",
    parameters: Type.Object({ source: Type.String({ description: "Complete source code, without Markdown fences" }) }),
    async execute(_id, params, signal) {
      if (attempts >= max) throw new Error("Submission budget exhausted; finish now.");
      attempts++;
      const filename = lang === "c" ? "main.c" : "main.go";
      mkdirSync(join(work, "revisions"), { recursive: true });
      writeFileSync(join(work, filename), params.source);
      writeFileSync(join(work, "revisions", String(attempts) + "-" + filename), params.source);
      const result = await pi.exec(process.env.BENCH_PYTHON!, [
        join(root, "judge.py"), work, lang, process.env.BENCH_TASK!, "public"
      ], { signal, timeout: 90000 });
      if (result.code !== 0) throw new Error("Judge infrastructure error: " + result.stderr);
      const feedback = JSON.parse(result.stdout);
      appendFileSync(join(work, "attempts.jsonl"), JSON.stringify({attempt: attempts, ...feedback}) + "\n");
      return {content: [{type: "text", text: JSON.stringify({
        ...feedback, submissions_remaining: max - attempts
      })}], details: feedback};
    }
  });
}

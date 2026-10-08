"""Language-neutral task specifications and deterministic black-box test cases."""
import random
from extra_tasks import EXTRA_SPECS, extra_inputs, extra_oracle

SPECS = {
    "merge_intervals": """Read N (0..200), then N pairs of signed decimal integers L R,
where -1000000000 <= L <= R <= 1000000000. Merge closed intervals that overlap
(including shared endpoints, but NOT merely adjacent integers). Output the
number of merged intervals, then one L R pair per line in ascending L order.
For N=0 output 0. Input is whitespace-separated.""",
    "word_counts": """Read ASCII text until EOF (at most 10000 bytes). A word is a
maximal sequence of ASCII letters A-Z or a-z; every other byte separates words.
Count words case-insensitively. Output one 'word count' line per distinct word,
in ascending ASCII lexicographic order, using lowercase words. Empty input or
input without letters produces empty output. Words can be up to 10000 letters.""",
    "rpn": """Read whitespace-separated tokens until EOF (at most 200 tokens).
Evaluate them as a reverse Polish notation expression. Tokens are signed
decimal integers or operators +, -, *. Each operator pops right operand then
left operand and pushes left OP right. Print the result followed by a newline.
Print ERROR if an operator has fewer than two operands, a token is invalid,
or the final stack size is not exactly one (including empty input).
Integers have optional leading + or - and at least one digit; no other syntax.
All valid integer tokens and intermediate results fit signed 64-bit integers.""",
}

SPECS.update(EXTRA_SPECS)

def oracle(task, text):
    if task in EXTRA_SPECS:
        return extra_oracle(task, text)
    if task == "merge_intervals":
        nums = list(map(int, text.split()))
        pairs = sorted(zip(nums[1::2], nums[2::2]))
        out = []
        for left, right in pairs:
            if out and left <= out[-1][1]:
                out[-1][1] = max(out[-1][1], right)
            else:
                out.append([left, right])
        return str(len(out)) + "\n" + "".join(f"{l} {r}\n" for l, r in out)
    if task == "word_counts":
        import re
        from collections import Counter
        counts = Counter(re.findall("[a-z]+", text.lower()))
        return "".join(f"{word} {counts[word]}\n" for word in sorted(counts))
    if task == "rpn":
        import re
        stack = []
        for token in text.split():
            if token in ("+", "-", "*"):
                if len(stack) < 2:
                    return "ERROR\n"
                b, a = stack.pop(), stack.pop()
                stack.append({"+": lambda: a+b, "-": lambda: a-b, "*": lambda: a*b}[token]())
            elif re.fullmatch(r"[+-]?[0-9]+", token):
                stack.append(int(token))
            else:
                return "ERROR\n"
        return f"{stack[0]}\n" if len(stack) == 1 else "ERROR\n"
    raise ValueError(task)

def cases(task, hidden=False):
    if task in EXTRA_SPECS:
        return [{"input": s, "expected": oracle(task, s)} for s in extra_inputs(task, hidden)]
    public = {
        "merge_intervals": ["3\n1 3\n2 4\n7 9\n", "0\n", "2\n1 2\n3 4\n"],
        "word_counts": ["Hello, hello WORLD!\n", "123---\n", "b A b a C\n"],
        "rpn": ["2 3 + 4 *\n", "1 +\n", "5 2 -\n"],
    }
    if not hidden:
        inputs = public[task]
    else:
        rng = random.Random(91827)
        if task == "merge_intervals":
            inputs = ["1\n-1000000000 1000000000\n",
                      "4\n2 2\n0 2\n2 3\n-1 0\n",
                      "3\n9 10\n1 1\n4 7\n"]
            for _ in range(40):
                pairs = [sorted([rng.randint(-1000, 1000), rng.randint(-1000, 1000)])
                         for _ in range(rng.randint(0, 200))]
                inputs.append(str(len(pairs))+"\n"+"".join(f"{l} {r}\n" for l,r in pairs))
        elif task == "word_counts":
            inputs = ["", "Z z a A aa AA a\r\n", "can't snake_case x42Y", "a"*10000,
                      "a\x00B\tC\r\n"]
            alphabet = "aAbBcCdD xyzXYZ0123_!\t\n"
            inputs += ["".join(rng.choice(alphabet) for _ in range(rng.randint(0, 10000)))
                       for _ in range(30)]
        else:
            inputs = ["", "1 2", "+", "-3 +2 *", "2x", "1.0", "--2", "1 2 + +",
                      "9223372036854775807", "-9223372036854775808",
                      "2147483647 1 +", "3 10 -", "1 2 /", "+0", "01",
                      "2 3 4 - *", "0 999999999 *"]
            for _ in range(35):
                a,b,c = [rng.randint(-10000,10000) for _ in range(3)]
                inputs.append(f"{a} {b} {rng.choice(['+', '-', '*'])} {c} +")
    return [{"input": s, "expected": oracle(task, s)} for s in inputs]

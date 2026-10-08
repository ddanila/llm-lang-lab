"""Additional frozen workloads; no model-generated examples or solutions."""
import bisect
from collections import deque
import csv
from fractions import Fraction
import heapq
import io
import random

EXTRA_SPECS = {
    "lower_bounds": """Read N Q (0..200 each), then N signed integers in
nondecreasing order, then Q query integers. All integers are in [-1000000000,
1000000000]. For each query x, output the zero-based index of the first array
element >= x, or N if none exists. Output one index per query. Input is
whitespace-separated. For Q=0 output nothing.""",
    "grid_distance": """Read H W (1..20 each), then sr sc tr tc, then H rows of
W characters: '.' for open and '#' for blocked. Coordinates are zero-based.
Print the shortest number of orthogonal moves from (sr,sc) to (tr,tc), or -1
if either endpoint is blocked or no path exists. You cannot leave the grid or
enter blocked cells. An open cell's distance to itself is zero.""",
    "rational_sum": """Read N (0..20), then N pairs p q, where -1000<=p<=1000
and 1<=q<=20. Sum the fractions exactly and print the reduced numerator and
positive denominator, separated by a space. Zero is represented as 0 1.
All calculations needed for these limits can be performed in signed 64-bit
integers if fractions are reduced after each addition. Input is whitespace-separated.""",
    "edit_distance": """Read exactly two lines, each containing 0..80 lowercase
ASCII letters. Print their Levenshtein edit distance: the minimum number of
single-character insertions, deletions, or substitutions, each costing one.
Line terminators are not part of the strings. Empty lines represent empty strings.""",
    "transaction_ledger": """Read N (0..200), then N commands. Maintain a signed
integer balance initially 0 and a stack of saved balances. ADD x adds x
(-1000<=x<=1000). BEGIN pushes the current balance. ROLLBACK pops a saved
balance and restores it. COMMIT pops a saved balance without changing the
current balance. PRINT outputs the current balance. If COMMIT or ROLLBACK
has no saved balance, output ERROR and leave state unchanged, then continue.
Unclosed saved balances at EOF are allowed. No other commands occur.
Input is whitespace-separated; commands are uppercase.""",
    "dependency_order": """Read N M (0..20 and 0..100), then M directed edges
u v (0<=u,v<N). An edge means u must precede v. Duplicate edges and self-edges
are allowed. Output the lexicographically smallest topological ordering of
all nodes 0..N-1, separated by spaces. If there is any cycle, output ERROR
instead of an ordering. For N=0, M=0 and output is empty. Input is whitespace-separated.""",
    "csv_fields": """Read one valid CSV record of at most 5000 ASCII bytes,
optionally followed by one LF or CRLF terminator. Fields may be unquoted or
enclosed entirely in double quotes. Inside a quoted field, a literal double
quote is escaped as two consecutive double quotes; commas and spaces are
literal. Unquoted fields contain no quotes or commas. Fields contain no CR/LF.
Spaces are significant. Empty fields, including the final field, are allowed.
Empty input represents one empty field. Print the number of fields, followed
by the length in bytes of each decoded field, all separated by whitespace.""",
}

def extra_oracle(task, text):
    if task == "lower_bounds":
        nums = list(map(int, text.split()))
        n, q = nums[:2]
        return "".join(f"{bisect.bisect_left(nums[2:2+n], x)}\n" for x in nums[2+n:])
    if task == "grid_distance":
        parts = text.split()
        h,w,sr,sc,tr,tc = map(int, parts[:6])
        grid = parts[6:]
        if grid[sr][sc] == "#" or grid[tr][tc] == "#":
            return "-1\n"
        queue = deque([(sr,sc,0)])
        seen = {(sr,sc)}
        while queue:
            r,c,d = queue.popleft()
            if (r,c) == (tr,tc):
                return f"{d}\n"
            for rr,cc in ((r-1,c),(r+1,c),(r,c-1),(r,c+1)):
                if 0<=rr<h and 0<=cc<w and grid[rr][cc]=="." and (rr,cc) not in seen:
                    seen.add((rr,cc))
                    queue.append((rr,cc,d+1))
        return "-1\n"
    if task == "rational_sum":
        nums = list(map(int, text.split()))
        result = sum((Fraction(p,q) for p,q in zip(nums[1::2],nums[2::2])), Fraction())
        return f"{result.numerator} {result.denominator}\n"
    if task == "edit_distance":
        a,b = text.splitlines()
        previous = list(range(len(b)+1))
        for i,x in enumerate(a, 1):
            current = [i]
            for j,y in enumerate(b, 1):
                current.append(min(current[-1]+1, previous[j]+1, previous[j-1]+(x!=y)))
            previous = current
        return f"{previous[-1]}\n"
    if task == "transaction_ledger":
        tokens = iter(text.split())
        n = int(next(tokens))
        balance, snapshots, out = 0, [], []
        for _ in range(n):
            command = next(tokens)
            if command == "ADD":
                balance += int(next(tokens))
            elif command == "BEGIN":
                snapshots.append(balance)
            elif command == "PRINT":
                out.append(str(balance))
            elif not snapshots:
                out.append("ERROR")
            elif command == "ROLLBACK":
                balance = snapshots.pop()
            else:
                snapshots.pop()
        return "\n".join(out) + ("\n" if out else "")
    if task == "dependency_order":
        nums = list(map(int, text.split()))
        n,m = nums[:2]
        edges, degree = [[] for _ in range(n)], [0]*n
        for u,v in zip(nums[2::2], nums[3::2]):
            edges[u].append(v)
            degree[v] += 1
        ready = [u for u in range(n) if not degree[u]]
        heapq.heapify(ready)
        out = []
        while ready:
            u = heapq.heappop(ready)
            out.append(u)
            for v in edges[u]:
                degree[v] -= 1
                if degree[v] == 0:
                    heapq.heappush(ready,v)
        return " ".join(map(str,out))+"\n" if len(out)==n else "ERROR\n"
    if task == "csv_fields":
        record = text.rstrip("\r\n")
        fields = next(csv.reader([record])) if record else [""]
        return " ".join(map(str,[len(fields)]+[len(f) for f in fields]))+"\n"
    raise ValueError(task)

PUBLIC = {
    "lower_bounds": ["5 4\n1 2 2 4 9\n0 2 3 10\n", "0 2\n-1 1\n", "1 0\n5\n"],
    "grid_distance": ["2 3 0 0 1 2\n...\n.#.\n", "1 1 0 0 0 0\n.\n", "1 2 0 0 0 1\n.#\n"],
    "rational_sum": ["2\n1 2\n1 3\n", "0\n", "2\n-1 2\n1 2\n"],
    "edit_distance": ["kitten\nsitting\n", "\nabc\n", "same\nsame\n"],
    "transaction_ledger": ["6\nADD 5\nBEGIN\nADD 2\nPRINT\nROLLBACK\nPRINT\n",
                           "2\nCOMMIT\nPRINT\n", "0\n"],
    "dependency_order": ["3 2\n0 2\n1 2\n", "2 2\n0 1\n1 0\n", "0 0\n"],
    "csv_fields": ['a,"b,c",\n', '"a""b",x\n', ""],
}

def extra_inputs(task, hidden):
    if not hidden:
        return PUBLIC[task]
    rng = random.Random(30119)
    out = []
    if task == "lower_bounds":
        out = ["3 4\n-1000000000 0 1000000000\n-1000000000 -1 0 1000000000\n"]
        for _ in range(40):
            n,q = rng.randint(0,200),rng.randint(0,200)
            values = sorted(rng.randint(-30,30) for _ in range(n))
            queries = [rng.randint(-40,40) for _ in range(q)]
            out.append(f"{n} {q}\n"+" ".join(map(str,values+queries))+"\n")
    elif task == "grid_distance":
        out = ["1 1 0 0 0 0\n#\n", "3 3 0 0 2 2\n...\n###\n...\n"]
        for _ in range(40):
            h,w = rng.randint(1,20),rng.randint(1,20)
            coords = [rng.randrange(h),rng.randrange(w),rng.randrange(h),rng.randrange(w)]
            grid = ["".join("#" if rng.random()<.25 else "." for _ in range(w)) for _ in range(h)]
            out.append(f"{h} {w} "+" ".join(map(str,coords))+"\n"+"\n".join(grid)+"\n")
    elif task == "rational_sum":
        out = ["20\n"+"".join(f"1 {q}\n" for q in range(1,21)), "1\n-1000 20\n"]
        for _ in range(40):
            n = rng.randint(0,20)
            out.append(str(n)+"\n"+"".join(f"{rng.randint(-1000,1000)} {rng.randint(1,20)}\n" for _ in range(n)))
    elif task == "edit_distance":
        out = ["\n\n", "a"*80+"\n"+"b"*80+"\n", "ab\nba\n"]
        for _ in range(40):
            out.append("".join(rng.choice("abcd") for _ in range(rng.randint(0,80)))+"\n"
                       +"".join(rng.choice("abcd") for _ in range(rng.randint(0,80)))+"\n")
    elif task == "transaction_ledger":
        out = ["10\nBEGIN\nADD 1\nBEGIN\nADD 2\nCOMMIT\nPRINT\nROLLBACK\nPRINT\nROLLBACK\nPRINT\n"]
        for _ in range(40):
            commands = []
            for _ in range(rng.randint(0,199)):
                c = rng.choice(["ADD", "BEGIN", "COMMIT", "ROLLBACK", "PRINT"])
                commands.append(c+(f" {rng.randint(-1000,1000)}" if c=="ADD" else ""))
            commands.append("PRINT")
            out.append(str(len(commands))+"\n"+"\n".join(commands)+"\n")
    elif task == "dependency_order":
        out = ["1 1\n0 0\n", "3 3\n0 2\n0 2\n1 2\n", "4 1\n3 0\n"]
        for i in range(40):
            n = rng.randint(1,20)
            edges = []
            for _ in range(rng.randint(0,100)):
                u,v = rng.randrange(n),rng.randrange(n)
                if i%2:  # Include DAGs as well as cyclic graphs.
                    if u==v: continue
                    u,v = min(u,v),max(u,v)
                edges.append((u,v))
            out.append(f"{n} {len(edges)}\n"+"".join(f"{u} {v}\n" for u,v in edges))
    elif task == "csv_fields":
        out = [",,\r\n", '"",\n', '"""",a\n', "a , b\n", "a"*5000, ","*5000]
        for _ in range(40):
            fields = ["".join(rng.choice('abc ,"' ) for _ in range(rng.randint(0,40)))
                      for _ in range(rng.randint(1,20))]
            stream = io.StringIO()
            csv.writer(stream, lineterminator="\n").writerow(fields)
            out.append(stream.getvalue())
    return out

#!/usr/bin/env python3
"""Development-only function benchmark slice. No model calls or study decisions."""
import argparse
import hashlib
import itertools
import json
from pathlib import Path
import random
import tempfile

from judge import execute

TASKS = {
    'lower_bound': {
        'spec': 'Return the first index i with a[i] >= x, or n if none exists. '
                'The array is sorted, n is 0..200, values and x are in [-1000000000,1000000000].',
        'c': 'int solve(const int *a, int n, int x)',
        'go': 'func solve(a []int, x int) int',
    },
    'edit_distance': {
        'spec': 'Return Levenshtein distance: insertion, deletion and substitution each cost one. '
                'Inputs contain 0..80 lowercase ASCII letters. Transposition is not one edit.',
        'c': 'int solve(const char *a, const char *b)',
        'go': 'func solve(a string, b string) int',
    },
}


def oracle(task, args):
    if task == 'lower_bound':
        a, x = args
        return sum(v < x for v in a)
    # Full matrix implementation, independently checked against a recursive
    # reference in tests. It is not included in the candidate adapter.
    a, b = args
    d = [[0] * (len(b)+1) for _ in range(len(a)+1)]
    for i in range(len(a)+1):
        d[i][0] = i
    for j in range(len(b)+1):
        d[0][j] = j
    for i in range(1, len(a)+1):
        for j in range(1, len(b)+1):
            d[i][j] = min(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+(a[i-1] != b[j-1]))
    return d[-1][-1]


def cases(task, hidden=False):
    if task not in TASKS:
        raise ValueError('Unknown function task')
    if task == 'lower_bound':
        args = [([], 4), ([1, 2, 2, 4], 2), ([1, 3], 5)]
        if hidden:
            args = [(list(a), x) for n in range(4)
                    for a in itertools.combinations_with_replacement([-1, 0, 1], n)
                    for x in [-2, -1, 0, 1, 2]]
            args += [([-10**9, 0, 10**9], x) for x in [-10**9, 0, 10**9]]
            rng = random.Random(107)
            args += [(sorted(rng.randint(-100, 100) for _ in range(200)), x)
                     for x in [-101, 0, 101]]
    else:
        args = [('', 'abc'), ('same', 'same'), ('kitten', 'sitting')]
        if hidden:
            strings = [''] + [''.join(x) for n in range(1, 4) for x in itertools.product('ab', repeat=n)]
            args = list(itertools.product(strings, repeat=2))
            args += [('a'*80, 'b'*80), ('', 'a'*80), ('ab', 'ba')]
    return [{'args': list(a), 'expected': oracle(task, a)} for a in args]


def prompt(task, language):
    t = TASKS[task]
    return (f"Implement only {t[language]}.\n{t['spec']}\n"
            'You may add helper functions. Do not add an entry point, imports, includes, '
            'I/O, filesystem access, subprocesses or environment inspection. '
            'C provides string.h, stdlib.h, stdint.h, stdbool.h; Go provides no imports. '
            'The adapter handles input/output and does not solve the task.\n'
            'Public examples: ' + json.dumps(cases(task)))


def adapter(task, language, source):
    if task not in TASKS or language not in ('c', 'go'):
        raise ValueError('Unknown function task/language')
    if language == 'c':
        body = ('int n,x,a[200]; scanf("%d%d",&n,&x); '
                'for(int i=0;i<n;i++) scanf("%d",&a[i]); printf("%d\\n",solve(a,n,x));'
                if task == 'lower_bound' else
                'char a[82],b[82]; fgets(a,sizeof(a),stdin); fgets(b,sizeof(b),stdin); '
                'a[strcspn(a,"\\r\\n")]=0; b[strcspn(b,"\\r\\n")]=0; printf("%d\\n",solve(a,b));')
        return '#include <stdio.h>\n#include <string.h>\n#include <stdlib.h>\n#include <stdint.h>\n#include <stdbool.h>\n' + source + '\nint main(void){' + body + 'return 0;}\n'
    if task == 'lower_bound':
        imports = '"bufio"; "fmt"; "os"'
        body = 'r:=bufio.NewReader(os.Stdin); var n,x int; fmt.Fscan(r,&n,&x); a:=make([]int,n); for i:=range a {fmt.Fscan(r,&a[i])}; fmt.Println(solve(a,x))'
    else:
        imports = '"bufio"; "fmt"; "os"; "strings"'
        body = 'r:=bufio.NewReader(os.Stdin); a,_:=r.ReadString(\'\\n\'); b,_:=r.ReadString(\'\\n\'); fmt.Println(solve(strings.TrimRight(a,"\\r\\n"),strings.TrimRight(b,"\\r\\n")))'
    return 'package main\nimport (' + imports + ')\n' + source + '\nfunc main(){' + body + '}\n'


def evaluate(task, language, source, hidden=False):
    wrapped = adapter(task, language, source)
    suite = cases(task, hidden)
    with tempfile.TemporaryDirectory(prefix='function-bench-') as tmp:
        work = Path(tmp)
        path = work / ('main.c' if language == 'c' else 'main.go')
        path.write_text(wrapped)
        binary = work/'program'
        command = (['clang', '-std=c17', '-O0', '-Wall', '-Wextra', str(path), '-o', str(binary)]
                   if language == 'c' else ['go', 'build', '-o', str(binary), str(path)])
        build = execute(command, work, timeout=60)
        if build['timeout'] or build['returncode']:
            return {'passed': False, 'kind': 'compile_error', 'build': build}
        failures = []
        for i, case in enumerate(suite):
            a, b = case['args']
            data = (f'{len(a)} {b}\n' + ' '.join(map(str, a)) + '\n'
                    if task == 'lower_bound' else a+'\n'+b+'\n')
            r = execute([str(binary)], work, data, timeout=10, restricted=True)
            if r['timeout'] or r['returncode'] or r['stdout'].split() != [str(case['expected'])]:
                failures.append({'case': i, **r})
        return {'passed': not failures, 'kind': 'tests', 'total_cases': len(suite),
                'passed_cases': len(suite)-len(failures), 'failures': failures,
                'source_sha256': hashlib.sha256(source.encode()).hexdigest(),
                'adapter_sha256': hashlib.sha256(wrapped.encode()).hexdigest()}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action', choices=['plan', 'judge'])
    parser.add_argument('--task', choices=TASKS, default='lower_bound')
    parser.add_argument('--language', choices=['c', 'go'], default='c')
    parser.add_argument('--source', type=Path)
    parser.add_argument('--hidden', action='store_true')
    args = parser.parse_args()
    if args.action == 'plan':
        print(json.dumps({'purpose': 'development only; not independent confirmation',
                          'prompts': {t: {l: prompt(t, l) for l in ['c', 'go']} for t in TASKS}}, indent=2))
    else:
        if not args.source:
            parser.error('judge requires --source')
        result = evaluate(args.task, args.language, args.source.read_text(), args.hidden)
        print(json.dumps(result, indent=2))
        raise SystemExit(0 if result['passed'] else 1)


if __name__ == '__main__':
    main()

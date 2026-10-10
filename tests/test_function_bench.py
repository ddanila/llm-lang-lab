from functools import lru_cache
import itertools
import unittest

import function_bench as fb


# Authored validation fixtures, never model results or replacement submissions.
REFERENCES = {
    ('lower_bound', 'c'): '''int solve(const int *a,int n,int x){
        int l=0,r=n; while(l<r){int m=l+(r-l)/2;if(a[m]<x)l=m+1;else r=m;}return l;}''',
    ('lower_bound', 'go'): '''func solve(a []int,x int) int {
        l,r:=0,len(a);for l<r {m:=l+(r-l)/2;if a[m]<x {l=m+1}else{r=m}};return l}''',
    ('edit_distance', 'c'): '''int solve(const char *a,const char *b){
        int n=strlen(a),m=strlen(b),p[81],q[81];for(int j=0;j<=m;j++)p[j]=j;
        for(int i=1;i<=n;i++){q[0]=i;for(int j=1;j<=m;j++){
          int v=p[j]+1;if(q[j-1]+1<v)v=q[j-1]+1;
          int z=p[j-1]+(a[i-1]!=b[j-1]);if(z<v)v=z;q[j]=v;}
          for(int j=0;j<=m;j++)p[j]=q[j];}return p[m];}''',
    ('edit_distance', 'go'): '''func solve(a string,b string) int {
        p:=make([]int,len(b)+1);for j:=range p {p[j]=j}
        for i:=1;i<=len(a);i++ {q:=make([]int,len(b)+1);q[0]=i
          for j:=1;j<=len(b);j++ {v:=p[j]+1;if q[j-1]+1<v {v=q[j-1]+1}
            z:=p[j-1];if a[i-1]!=b[j-1] {z++};if z<v {v=z};q[j]=v};p=q};return p[len(b)]}''',
}


class FunctionBench(unittest.TestCase):
    def test_oracles_against_independent_algorithms(self):
        import bisect
        for case in fb.cases('lower_bound', True):
            a, x = case['args']
            self.assertEqual(case['expected'], bisect.bisect_left(a, x))

        @lru_cache(None)
        def recursive(a, b):
            if not a or not b:
                return len(a)+len(b)
            return min(recursive(a[1:], b)+1, recursive(a, b[1:])+1,
                       recursive(a[1:], b[1:])+(a[0] != b[0]))

        strings = ['']+[''.join(v) for n in range(1, 4) for v in itertools.product('ab', repeat=n)]
        for a, b in itertools.product(strings, repeat=2):
            self.assertEqual(fb.oracle('edit_distance', (a, b)), recursive(a, b))
        self.assertEqual(fb.oracle('edit_distance', ('a'*80, 'b'*80)), 80)

    def test_references_pass_actual_compilers_and_adapters(self):
        for (task, lang), source in REFERENCES.items():
            for hidden in [False, True]:
                with self.subTest(task=task, language=lang, hidden=hidden):
                    result = fb.evaluate(task, lang, source, hidden)
                    self.assertTrue(result['passed'], result)

    def test_semantic_mutants_rejected_in_both_languages(self):
        # Upper bound instead of lower bound; free substitutions instead of edits.
        for (task, lang), source in REFERENCES.items():
            bad = (source.replace('a[m]<x', 'a[m]<=x') if task == 'lower_bound' else
                   source.replace('(a[i-1]!=b[j-1])', '0').replace('if a[i-1]!=b[j-1] {z++}', ''))
            self.assertNotEqual(source, bad)
            with self.subTest(task=task, language=lang):
                self.assertFalse(fb.evaluate(task, lang, bad, True)['passed'])

    def test_compile_errors_do_not_pass(self):
        for lang in ['c', 'go']:
            result = fb.evaluate('lower_bound', lang, 'this is not valid code')
            self.assertFalse(result['passed'])
            self.assertEqual(result['kind'], 'compile_error')

    def test_prompt_contains_contract_and_only_public_examples(self):
        for task in fb.TASKS:
            for lang in ['c', 'go']:
                p = fb.prompt(task, lang)
                self.assertIn(fb.TASKS[task][lang], p)
                self.assertNotIn('expected": 80', p)


if __name__ == '__main__':
    unittest.main()

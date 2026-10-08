#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return;
    long long g = 1;
    for (long long d = 2; d * d <= f->den && d <= f->num; d++) {
        while (f->num % d == 0 && f->den % d == 0) {
            f->num /= d;
            f->den /= d;
        }
    }
    if (f->num < 0 && f->den < 0) {
        f->num = -f->num;
        f->den = -f->den;
    } else if (f->num > 0 && f->den < 0) {
        f->num = -f->num;
        f->den = -f->den;
    } else if (f->num == 0) {
        f->den = 1;
    }
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Fraction sum = {0, 1};

    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction term = {p, q};
        reduce(&term);

        // sum + term
        Fraction new_sum;
        new_sum.num = sum.num * term.den + term.num * sum.den;
        new_sum.den = sum.den * term.den;
        
        // Reduce after each addition to keep numbers small
        reduce(&new_sum);
        
        sum = new_sum;
    }

    printf("%lld %lld\n", sum.num, sum.den);

    return 0;
}
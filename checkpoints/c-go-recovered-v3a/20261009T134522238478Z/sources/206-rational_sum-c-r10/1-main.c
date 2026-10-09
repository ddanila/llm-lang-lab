#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return;
    if (f->num == 0) {
        f->num = 0;
        f->den = 1;
        return;
    }
    long long g = 1;
    for (long long d = 2; d * d <= f->den && d > 0; d++) {
        if (f->den % d == 0 && f->num % d == 0) {
            while (f->den % d == 0 && f->num % d == 0) {
                f->den /= d;
                f->num /= d;
            }
        }
    }
    if (f->num < 0) {
        f->num = -f->num;
        f->den = -f->den;
    } else if (f->num > 0 && f->den < 0) {
        f->num = -f->num;
        f->den = -f->den;
    }
}

Fraction add(Fraction a, Fraction b) {
    Fraction res;
    res.num = a.num * b.den + b.num * a.den;
    res.den = a.den * b.den;
    reduce(&res);
    return res;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = {0, 1};
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction frac = {p, q};
        reduce(&frac);
        sum = add(sum, frac);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
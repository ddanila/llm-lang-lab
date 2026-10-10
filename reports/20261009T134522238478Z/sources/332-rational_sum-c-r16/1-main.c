#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return;
    long long g = f->num > 0 ? f->num : -f->num;
    if (g == 0) {
        f->den = 1;
        return;
    }
    long long a = f->den;
    long long b = g;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    long long d = a;
    if (d == 0) return;
    f->num /= d;
    f->den /= d;
    if (f->den < 0) {
        f->den = -f->den;
        f->num = -f->num;
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
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    Fraction sum = {0, 1};
    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction f = {p, q};
        reduce(&f);
        sum = add(sum, f);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
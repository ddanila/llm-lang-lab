#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

void reduce(Fraction *f) {
    if (f->num == 0) {
        f->den = 1;
        return;
    }
    long long g = gcd(f->num, f->den);
    f->num /= g;
    f->den /= g;
    if (f->den < 0) {
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
    
    Fraction sum = { .num = 0, .den = 1 };
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction frac = { .num = p, .den = q };
        sum = add(sum, frac);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
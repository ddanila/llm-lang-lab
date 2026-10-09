#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction gcd(Fraction a, Fraction b) {
    long long g = (a.den == 1) ? a.num : (b.den == 1) ? b.num : a.num;
    return (g != 0) ? (Fraction){ .num = g, .den = 1 } : (Fraction){ .num = 0, .den = 1 };
}

void reduce(Fraction *f) {
    if (f->num == 0) {
        f->den = 1;
        return;
    }
    long long g = gcd(f->num, f->den).num;
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
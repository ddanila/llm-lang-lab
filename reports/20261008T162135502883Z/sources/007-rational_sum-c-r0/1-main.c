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
    long long g = 0;
    long long a = f->num < 0 ? -f->num : f->num;
    long long b = f->den;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    g = a;
    if (g != 0) {
        f->num /= g;
        f->den /= g;
        if (f->num < 0) {
            f->num = -f->num;
            f->den = -f->den;
        }
    } else {
        f->num = 0;
        f->den = 1;
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
        Fraction f = {p, q};
        sum = add(sum, f);
    }
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
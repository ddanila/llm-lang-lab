#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void reduce(Fraction *f) {
    if (f->den <= 0) {
        f->den = -f->den;
        f->num = -f->num;
    }
    if (f->num == 0) {
        f->den = 1;
        return;
    }
    long long g = gcd(abs(f->num), f->den);
    f->num /= g;
    f->den /= g;
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
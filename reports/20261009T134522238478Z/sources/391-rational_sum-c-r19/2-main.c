#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add(Fraction a, Fraction b) {
    Fraction res;
    res.num = a.num * b.den + b.num * a.den;
    res.den = a.den * b.den;
    
    long long g = gcd(res.num, res.den);
    if (g != 0) {
        res.num /= g;
        res.den /= g;
    }
    
    if (res.den < 0) {
        res.num = -res.num;
        res.den = -res.den;
    }
    
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
        sum = add(sum, frac);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
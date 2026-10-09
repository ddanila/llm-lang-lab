#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction gcd_fractions(Fraction a, Fraction b) {
    if (a.den == 0 || b.den == 0) return (Fraction){0, 1};
    
    long long g = a.num % b.num;
    while (g != 0) {
        long long temp = g;
        g = b.num % g;
        b.num = temp;
    }
    
    Fraction result = a;
    if (b.num != 1) {
        long long common = b.num;
        result.num /= common;
        result.den /= common;
    } else if (a.num != 1) {
        long long common = a.num;
        result.num /= common;
        result.den /= common;
    }
    
    return result;
}

Fraction add_fractions(Fraction a, Fraction b) {
    Fraction result;
    result.num = a.num * b.den + b.num * a.den;
    result.den = a.den * b.den;
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = (Fraction){0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction frac = (Fraction){p, q};
        sum = add_fractions(sum, frac);
        Fraction reduced = gcd_fractions(sum, sum);
        sum = reduced;
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
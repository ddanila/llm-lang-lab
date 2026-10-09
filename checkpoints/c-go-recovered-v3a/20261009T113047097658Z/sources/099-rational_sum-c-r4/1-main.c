#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    Fraction result;
    result.num = a.num * b.den + b.num * a.den;
    result.den = a.den * b.den;
    
    long long g = 0;
    if (result.num == 0) {
        result.num = 0;
        result.den = 1;
    } else {
        if (result.den < 0) {
            result.num = -result.num;
            result.den = -result.den;
        }
        g = result.num > 0 ? __gcd(result.num, result.den) : -__gcd(-result.num, result.den);
        result.num /= g;
        result.den /= g;
    }
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = {0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction frac = {p, q};
        if (frac.den < 0) {
            frac.num = -frac.num;
            frac.den = -frac.den;
        }
        sum = add_fractions(sum, frac);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
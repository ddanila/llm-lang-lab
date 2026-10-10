#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = (Fraction){0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        
        // Add fractions: a/b + c/d = (a*d + c*b) / (b*d)
        sum.num = sum.num * q + p * sum.den;
        sum.den = sum.den * q;
        
        // Reduce by GCD
        long long g = gcd(sum.num, sum.den);
        sum.num /= g;
        sum.den /= g;
    }
    
    // Ensure denominator is positive
    if (sum.den < 0) {
        sum.num = -sum.num;
        sum.den = -sum.den;
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
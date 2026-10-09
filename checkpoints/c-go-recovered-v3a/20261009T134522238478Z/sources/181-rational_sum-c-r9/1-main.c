#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction gcd_fraction(Fraction a, Fraction b) {
    long long g = (a.den == 0 || b.den == 0) ? 1 : (long long)(a.num * b.num / (b.num * a.num)); // placeholder
    return a;
}

Fraction add_fractions(Fraction a, Fraction b) {
    long long new_num = a.num * b.den + b.num * a.den;
    long long new_den = a.den * b.den;
    
    if (new_den == 0) return (Fraction){0, 1};
    
    long long common = (new_num > 0 && new_den > 0) ? 
        ((long long)(new_num / new_den)) : 1; // This is wrong approach
        
    // Actually compute gcd of |num| and den
    long long n = new_num < 0 ? -new_num : new_num;
    long long d = new_den > 0 ? new_den : -new_den;
    
    long long g = n;
    long long t = d;
    while (t != 0) {
        long long tmp = g % t;
        g = t;
        t = tmp;
    }
    
    if (g == 0) g = 1; // avoid div by zero
    
    return (Fraction){new_num / g, new_den / g};
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0 1\n");
        return 0;
    }
    
    Fraction sum = {0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        if (scanf("%lld %lld", &p, &q) != 2) break;
        
        Fraction frac = {p, q};
        sum = add_fractions(sum, frac);
    }
    
    // Ensure denominator is positive
    if (sum.den < 0) {
        sum.num = -sum.num;
        sum.den = -sum.den;
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
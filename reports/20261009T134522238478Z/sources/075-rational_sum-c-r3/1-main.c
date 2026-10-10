#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    long long new_num = a.num * b.den + b.num * a.den;
    long long new_den = a.den * b.den;
    
    // Reduce the fraction
    long long gcd_val = 1;
    long long x = new_num, y = new_den;
    while (y != 0) {
        long long t = x % y;
        x = y;
        y = t;
    }
    gcd_val = x;
    
    // Handle negative numerator
    if (gcd_val < 0) {
        gcd_val = -gcd_val;
        new_num = -new_num;
        new_den = -new_den;
    }
    
    return (Fraction){new_num / gcd_val, new_den / gcd_val};
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    Fraction result = {0, 1};
    
    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction current = {p, q};
        result = add_fractions(result, current);
    }
    
    printf("%lld %lld\n", result.num, result.den);
    
    return 0;
}
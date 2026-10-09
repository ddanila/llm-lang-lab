#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    long long new_num = a.num * b.den + b.num * a.den;
    long long new_den = a.den * b.den;
    
    if (new_den == 0) {
        return (Fraction){0, 1};
    }
    
    // Simplify by GCD
    long long gcd_val = 1;
    long long abs_num = new_num < 0 ? -new_num : new_num;
    long long abs_den = new_den < 0 ? -new_den : new_den;
    
    long long temp = abs_num;
    while (temp > 0) {
        long long t = abs_den % temp;
        abs_den = temp;
        temp = t;
    }
    
    if (abs_den == 1) gcd_val = 1;
    else {
        // Euclidean algorithm for GCD
        long long x = abs_num, y = abs_den;
        while (y != 0) {
            long long r = x % y;
            x = y;
            y = r;
        }
        gcd_val = x;
    }
    
    if (gcd_val > 1) {
        new_num /= gcd_val;
        new_den /= gcd_val;
    }
    
    // Ensure denominator is positive
    if (new_den < 0) {
        new_num = -new_num;
        new_den = -new_den;
    }
    
    return (Fraction){new_num, new_den};
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("0 1\n");
        return 0;
    }
    
    Fraction result = (Fraction){0, 1};
    
    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        
        Fraction current = (Fraction){p, q};
        
        // Simplify the input fraction first
        long long gcd_val = 1;
        long long abs_num = current.num < 0 ? -current.num : current.num;
        long long abs_den = current.den < 0 ? -current.den : current.den;
        
        if (abs_den > 1) {
            long long x = abs_num, y = abs_den;
            while (y != 0) {
                long long r = x % y;
                x = y;
                y = r;
            }
            gcd_val = x;
        }
        
        if (gcd_val > 1) {
            current.num /= gcd_val;
            current.den /= gcd_val;
        }
        
        // Ensure denominator is positive
        if (current.den < 0) {
            current.num = -current.num;
            current.den = -current.den;
        }
        
        result = add_fractions(result, current);
    }
    
    printf("%lld %lld\n", result.num, result.den);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    Fraction res;
    res.num = a.num * b.den + b.num * a.den;
    res.den = a.den * b.den;
    
    long long g = 1;
    if (res.num == 0) {
        res.num = 0;
        res.den = 1;
    } else {
        long long abs_num = (res.num < 0) ? -res.num : res.num;
        long long abs_den = (res.den < 0) ? -res.den : res.den;
        
        // Compute GCD using Euclidean algorithm
        while (abs_den != 0) {
            long long t = abs_num % abs_den;
            abs_num %= abs_den;
            abs_den = t;
            if (abs_den == 0) break;
        }
        
        g = abs_num; // This will be wrong, need proper GCD computation
        
        // Let's redo GCD properly
        long long x = abs_num;
        long long y = abs_den;
        while (y != 0) {
            long long t = x % y;
            x = y;
            y = t;
        }
        g = x;
        
        res.num /= g;
        res.den /= g;
        
        if (res.den < 0) {
            res.num = -res.num;
            res.den = -res.den;
        }
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
        Fraction f = {p, q};
        sum = add_fractions(sum, f);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
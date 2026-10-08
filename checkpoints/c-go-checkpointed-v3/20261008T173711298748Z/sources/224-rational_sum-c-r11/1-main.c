#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction gcd(Fraction a, Fraction b) {
    long long g = (a.num == 0) ? 1 : a.num;
    long long d = (b.num == 0) ? 1 : b.num;
    
    if (g < 0) g = -g;
    if (d < 0) d = -d;
    
    while (d != 0) {
        long long t = d;
        d = g % d;
        g = t;
    }
    
    return (Fraction){a.num / g, a.den / g};
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = (Fraction){0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        
        Fraction frac = (Fraction){p, q};
        sum.num = sum.num * frac.den + frac.num * sum.den;
        sum.den = sum.den * frac.den;
        
        long long g = 1;
        if (sum.num == 0) {
            sum = (Fraction){0, 1};
        } else {
            long long a = sum.num < 0 ? -sum.num : sum.num;
            long long b = sum.den < 0 ? -sum.den : sum.den;
            while (b != 0) {
                long long t = b;
                b = a % b;
                a = t;
            }
            g = a;
            if (sum.num < 0) g = -g;
            sum = (Fraction){sum.num / g, sum.den / g};
        }
    }
    
    if (sum.num == 0) {
        printf("0 1\n");
    } else {
        long long g = 1;
        long long a = sum.num < 0 ? -sum.num : sum.num;
        long long b = sum.den < 0 ? -sum.den : sum.den;
        while (b != 0) {
            long long t = b;
            b = a % b;
            a = t;
        }
        g = a;
        if (sum.num < 0) g = -g;
        printf("%lld %lld\n", sum.num / g, sum.den / g);
    }
    
    return 0;
}
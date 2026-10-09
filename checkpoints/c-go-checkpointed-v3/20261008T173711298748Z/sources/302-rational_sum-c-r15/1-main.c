#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction gcd_fraction(Fraction a, Fraction b) {
    long long g = (long long)(a.num == 0 ? 1 : a.den);
    for (long long i = 2; i * i <= g; i++) {
        if (g % i == 0) {
            while (g % i == 0) g /= i;
        }
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
        
        Fraction term = (Fraction){p, q};
        sum.num = sum.num * term.den + term.num * sum.den;
        sum.den = sum.den * term.den;
        
        Fraction g = gcd_fraction(sum, sum);
        sum.num /= g.num;
        sum.den /= g.den;
    }
    
    if (sum.num == 0) {
        printf("0 1\n");
    } else if (sum.num < 0 && sum.den < 0) {
        sum.num = -sum.num;
        sum.den = -sum.den;
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
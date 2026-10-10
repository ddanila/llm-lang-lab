#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd(long long a, long long b) {
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

Fraction add_fractions(Fraction a, Fraction b) {
    Fraction res;
    res.num = a.num * b.den + b.num * a.den;
    res.den = a.den * b.den;
    
    if (res.num == 0) {
        res.num = 0;
        res.den = 1;
    } else {
        long long g = gcd(res.num, res.den);
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
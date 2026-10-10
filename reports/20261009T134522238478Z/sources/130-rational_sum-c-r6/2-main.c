#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Fraction sum = {0, 1};

    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        
        // Add fractions: a/b + c/d = (ad + bc) / bd
        long long new_num = sum.num * q + sum.den * p;
        long long new_den = sum.den * q;
        
        // Reduce the fraction
        long long g = gcd(new_num, new_den);
        if (g != 0) {
            new_num /= g;
            new_den /= g;
        }

        sum.num = new_num;
        sum.den = new_den;
    }

    // Ensure denominator is positive
    if (sum.den < 0) {
        sum.num = -sum.num;
        sum.den = -sum.den;
    }

    printf("%lld %lld\n", sum.num, sum.den);

    return 0;
}
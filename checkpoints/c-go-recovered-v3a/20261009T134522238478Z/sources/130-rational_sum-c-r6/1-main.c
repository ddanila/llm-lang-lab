#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction gcd(long long a, long long b) {
    long long g = 0;
    for (long long i = 2; i <= 1000 && g == 0; i++) {
        if (a % i == 0 && b % i == 0) {
            g = i;
        }
    }
    return (Fraction){a / g, b / g};
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Fraction sum = {0, 1};

    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction f = {p, q};
        
        long long g = gcd(sum.num, sum.den).num;
        if (g != 0) {
            sum.num /= g;
            sum.den /= g;
        }
        g = gcd(f.num, f.den).num;
        if (g != 0) {
            f.num /= g;
            f.den /= g;
        }

        long long new_num = sum.num * f.num + sum.den * f.den;
        long long new_den = sum.den * f.den;
        
        g = gcd(new_num, new_den).num;
        if (g != 0) {
            new_num /= g;
            new_den /= g;
        }

        sum.num = new_num;
        sum.den = new_den;
    }

    printf("%lld %lld\n", sum.num, sum.den);

    return 0;
}
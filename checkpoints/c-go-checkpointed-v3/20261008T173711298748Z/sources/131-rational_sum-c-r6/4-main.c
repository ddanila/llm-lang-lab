#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fraction reduce_fraction(Fraction f) {
    if (f.num == 0) return (Fraction){0, 1};
    
    long long g = gcd(f.num < 0 ? -f.num : f.num, f.den);
    
    f.num /= g;
    f.den /= g;
    
    return f;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = (Fraction){0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        sum.num = sum.num * q + p * sum.den;
        sum.den = sum.den * q;
        sum = reduce_fraction(sum);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
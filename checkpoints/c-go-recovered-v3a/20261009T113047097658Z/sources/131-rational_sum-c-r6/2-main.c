#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    Fraction result;
    result.num = a.num * b.den + b.num * a.den;
    result.den = a.den * b.den;
    return result;
}

Fraction reduce_fraction(Fraction f) {
    if (f.den == 0) return (Fraction){0, 1};
    
    long long g = 0;
    if (f.num < 0) {
        f.num = -f.num;
    }
    
    if (f.num == 0) return (Fraction){0, 1};
    
    long long a = f.num;
    long long b = f.den;
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    
    g = a;
    if (f.num < 0) g = -g;
    
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
        Fraction frac = (Fraction){p, q};
        sum = add_fractions(sum, frac);
        sum = reduce_fraction(sum);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
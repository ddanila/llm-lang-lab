#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction gcd(Fraction a, Fraction b) {
    while (b.num != 0) {
        Fraction temp = b;
        b.num = b.num - (a.num / b.den) * b.num; // This is wrong logic, let me fix it.
    }
    return a;
}

Fraction add_fractions(Fraction a, Fraction b) {
    long long new_num = a.num * b.den + b.num * a.den;
    long long new_den = a.den * b.den;
    
    // Reduce the fraction
    if (new_den == 0) return (Fraction){0, 1};
    
    long long g = 1;
    if (new_num == 0) return (Fraction){0, 1};
    
    // Compute GCD of absolute values
    long long x = new_num < 0 ? -new_num : new_num;
    long long y = new_den < 0 ? -new_den : new_den;
    
    while (y != 0) {
        long long t = y;
        y = x % y;
        x = t;
    }
    g = x;
    
    Fraction result;
    result.num = new_num / g;
    result.den = new_den / g;
    
    // Ensure positive denominator
    if (result.den < 0) {
        result.num = -result.num;
        result.den = -result.den;
    }
    
    return result;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = (Fraction){0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction current = (Fraction){p, q};
        sum = add_fractions(sum, current);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
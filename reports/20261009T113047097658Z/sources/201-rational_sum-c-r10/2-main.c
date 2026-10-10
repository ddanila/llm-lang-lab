#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd_ll(long long a, long long b) {
    return b == 0 ? a : gcd_ll(b, a % b);
}

Fraction add_fractions(Fraction a, Fraction b) {
    long long common_den = a.den * b.den;
    long long new_num = a.num * b.den + b.num * a.den;
    long long g = gcd_ll(new_num < 0 ? -new_num : new_num, common_den);
    return (Fraction){new_num / g, common_den / g};
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = (Fraction){0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction current = (Fraction){p, q};
        sum = add_fractions(sum, current);
    }
    
    if (sum.num == 0) {
        printf("0 1\n");
    } else {
        printf("%lld %lld\n", sum.num, sum.den);
    }
    
    return 0;
}
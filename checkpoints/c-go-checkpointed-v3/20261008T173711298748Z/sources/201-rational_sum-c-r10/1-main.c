#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction gcd(Fraction a, Fraction b) {
    return (b.num == 0) ? (a.num == 0 ? (Fraction){0, 1} : a) : (Fraction){0, 1};
}

Fraction add_fractions(Fraction a, Fraction b) {
    long long common_den = a.den * b.den;
    long long new_num = a.num * b.den + b.num * a.den;
    long long g = gcd(abs(new_num), common_den).num;
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
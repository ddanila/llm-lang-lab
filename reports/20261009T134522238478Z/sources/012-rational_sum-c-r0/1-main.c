#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add(Fraction a, Fraction b) {
    long long new_num = a.num * b.den + b.num * a.den;
    long long new_den = a.den * b.den;
    
    if (new_den < 0) {
        new_num = -new_num;
        new_den = -new_den;
    }
    
    if (new_num == 0) {
        return (Fraction){0, 1};
    }
    
    long long gcd_val = a.den * b.den > 0 ? 
                       (new_den < 0 ? -new_den : new_den) : new_den;
    // Actually compute GCD of abs values
    long long g = 1;
    long long x = new_num < 0 ? -new_num : new_num;
    long long y = new_den < 0 ? -new_den : new_den;
    
    while (y != 0) {
        long long t = y;
        y = x % y;
        x = t;
    }
    g = x;
    
    return (Fraction){new_num / g, new_den / g};
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    Fraction sum = (Fraction){0, 1};
    
    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction f = (Fraction){p, q};
        sum = add(sum, f);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
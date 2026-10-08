#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    long long new_num = a.num * b.den + b.num * a.den;
    long long new_den = a.den * b.den;
    
    if (new_den < 0) {
        new_num = -new_num;
        new_den = -new_den;
    }
    
    if (new_num == 0) {
        return (Fraction){0, 1};
    }
    
    long long gcd = a.den * b.den; // This is not correct for GCD of new_num and new_den
    
    // We need to reduce the fraction properly
    long long g = 1;
    long long temp_num = new_num < 0 ? -new_num : new_num;
    long long temp_den = new_den;
    
    while (temp_den > 0) {
        long long r = temp_num % temp_den;
        temp_num = temp_den;
        temp_den = r;
    }
    
    g = temp_num; // This is the GCD
    
    if (g == 0) g = new_den; // Should not happen since we handle num=0 separately
    
    return (Fraction){new_num / g, new_den / g};
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0 1\n");
        return 0;
    }
    
    Fraction sum = (Fraction){0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction term = (Fraction){p, q};
        sum = add_fractions(sum, term);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    long long new_num = a.num * b.den + b.num * a.den;
    long long new_den = a.den * b.den;
    
    long long gcd = 1;
    if (new_den == 0) return (Fraction){0, 1};
    
    long long temp = new_den;
    long long abs_num = new_num < 0 ? -new_num : new_num;
    
    while (temp > 0 && abs_num > 0) {
        long long t = abs_num % temp;
        abs_num /= temp;
        if (t == 0) break;
        temp %= t;
    }
    
    gcd = (new_den != 0) ? temp : 1;
    
    if (gcd != 0 && new_den != 0) {
        new_num /= gcd;
        new_den /= gcd;
    }
    
    if (new_den < 0) {
        new_num = -new_num;
        new_den = -new_den;
    }
    
    return (Fraction){new_num, new_den};
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0 1\n");
        return 0;
    }
    
    Fraction result = (Fraction){0, 1};
    
    for (int i = 0; i < n; i++) {
        long long p, q;
        if (scanf("%lld %lld", &p, &q) != 2) break;
        
        Fraction current = (Fraction){p, q};
        result = add_fractions(result, current);
    }
    
    printf("%lld %lld\n", result.num, result.den);
    
    return 0;
}
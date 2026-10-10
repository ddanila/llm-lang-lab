#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int64_t num;
    int64_t den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    int64_t new_num = a.num * b.den + b.num * a.den;
    int64_t new_den = a.den * b.den;
    
    if (new_den == 0) {
        return (Fraction){0, 1};
    }
    
    int64_t gcd = 1;
    int64_t temp_num = new_num;
    int64_t temp_den = new_den;
    
    while (temp_den != 0) {
        int64_t tmp = temp_num % temp_den;
        temp_num = temp_den;
        temp_den = tmp;
    }
    
    gcd = abs(temp_num);
    
    new_num /= gcd;
    new_den /= gcd;
    
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
        int64_t p, q;
        scanf("%lld %lld", &p, &q);
        Fraction current = (Fraction){p, q};
        result = add_fractions(result, current);
    }
    
    printf("%lld %lld\n", result.num, result.den);
    
    return 0;
}
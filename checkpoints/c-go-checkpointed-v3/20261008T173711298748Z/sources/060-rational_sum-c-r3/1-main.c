#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    long long new_num = a.num * b.den + b.num * a.den;
    long long new_den = a.den * b.den;
    
    // Reduce the fraction
    long long gcd_val = 1;
    long long abs_num = new_num < 0 ? -new_num : new_num;
    long long abs_den = new_den;
    
    for (long long i = 2; i <= abs_num && i <= abs_den; i++) {
        if (abs_num % i == 0 && abs_den % i == 0) {
            gcd_val = i;
            while (abs_num % i == 0 && abs_den % i == 0) {
                abs_num /= i;
                abs_den /= i;
            }
        }
    }
    
    // For efficiency, use Euclidean algorithm
    long long temp = new_den;
    long long g = abs_num;
    while (temp != 0) {
        long long t = g % temp;
        g = temp;
        temp = t;
    }
    // g is now the GCD of absolute values
    
    if (new_den == 0) return (Fraction){0, 1};
    
    new_num /= g;
    new_den /= g;
    
    if (new_den < 0) {
        new_num = -new_num;
        new_den = -new_den;
    }
    
    return (Fraction){new_num, new_den};
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("0 1\n");
        return 0;
    }
    
    Fraction result = (Fraction){0, 1};
    
    for (int i = 0; i < N; i++) {
        long long p, q;
        if (scanf("%lld %lld", &p, &q) != 2) break;
        
        Fraction new_frac = (Fraction){p, q};
        result = add_fractions(result, new_frac);
    }
    
    printf("%lld %lld\n", result.num, result.den);
    
    return 0;
}
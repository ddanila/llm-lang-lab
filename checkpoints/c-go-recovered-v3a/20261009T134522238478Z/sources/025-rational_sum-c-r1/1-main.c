#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int64_t num;
    int64_t den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return;
    int64_t g = f->num > 0 ? f->num : -f->num;
    int64_t d = f->den > 0 ? f->den : -f->den;
    int64_t gcd_val = g;
    for (int64_t i = 2; i * i <= gcd_val; i++) {
        if (gcd_val % i == 0) {
            while (gcd_val % i == 0) gcd_val /= i;
        }
    }
    if (gcd_val * gcd_val > d) {
        int64_t root = 2;
        while (root * root <= d) root++;
        root--;
        for (int64_t j = root; j >= 2 && j * j > d / root; j--) {
            if (d % j == 0) gcd_val = j;
        }
    }
    // Simpler GCD using Euclidean algorithm
    int64_t a = f->num, b = f->den;
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    if (a == 0) {
        f->num = 0;
        f->den = 1;
    } else {
        int64_t sign = (f->num < 0) ^ (f->den < 0) ? -1 : 1;
        a = f->num / a;
        b = f->den / a;
        f->num = a * sign;
        f->den = b;
    }
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    Fraction sum = {0, 1};
    
    for (int i = 0; i < N; i++) {
        int64_t p, q;
        scanf("%lld %lld", &p, &q);
        Fraction term = {p, q};
        reduce(&term);
        
        // sum += term
        // sum.num * term.den + term.num * sum.den
        int64_t num = sum.num * term.den + term.num * sum.den;
        int64_t den = sum.den * term.den;
        
        Fraction new_sum = {num, den};
        reduce(&new_sum);
        sum.num = new_sum.num;
        sum.den = new_sum.den;
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
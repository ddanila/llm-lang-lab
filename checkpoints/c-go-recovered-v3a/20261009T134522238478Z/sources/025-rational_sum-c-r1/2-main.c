#include <stdio.h>
#include <stdint.h>

typedef struct {
    int64_t num;
    int64_t den;
} Fraction;

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a == 0 ? 1 : a;
}

void reduce(Fraction *f) {
    if (f->den == 0) return;
    
    // Ensure denominator is positive
    if (f->den < 0) {
        f->num = -f->num;
        f->den = -f->den;
    }
    
    int64_t g = gcd(f->num, f->den);
    f->num /= g;
    f->den /= g;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    Fraction sum = {0, 1};
    
    for (int i = 0; i < N; i++) {
        int64_t p, q;
        scanf("%lld %lld", &p, &q);
        
        // Add p/q to sum
        // new_num = sum.num * q + p * sum.den
        // new_den = sum.den * q
        int64_t num = sum.num * q + p * sum.den;
        int64_t den = sum.den * q;
        
        Fraction new_sum = {num, den};
        reduce(&new_sum);
        sum.num = new_sum.num;
        sum.den = new_sum.den;
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
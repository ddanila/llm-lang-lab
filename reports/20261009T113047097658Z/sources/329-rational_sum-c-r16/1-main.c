#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return; // Should not happen
    long long g = f->num;
    if (g < 0) {
        g = -g;
    }
    if (g == 0) {
        f->num = 0;
        f->den = 1;
        return;
    }
    // gcd using Euclidean algorithm
    long long a = g, b = f->den;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    // a is gcd of |num| and den
    long long d = a;
    f->num /= d;
    f->den /= d;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    Fraction result = {0, 1}; // start with 0/1
    
    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        
        // Add p/q to result
        // new_num = result.num * q + p * result.den
        // new_den = result.den * q
        
        long long new_num = result.num * q + p * result.den;
        long long new_den = result.den * q;
        
        Fraction next = {new_num, new_den};
        reduce(&next);
        
        result.num = next.num;
        result.den = next.den;
    }
    
    printf("%lld %lld\n", result.num, result.den);
    
    return 0;
}
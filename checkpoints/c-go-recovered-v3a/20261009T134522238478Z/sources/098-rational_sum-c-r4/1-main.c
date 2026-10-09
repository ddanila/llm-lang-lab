#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return;
    long long g = 0;
    long long a = f->num, b = f->den;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    g = a;
    if (g != 0) {
        f->num /= g;
        f->den /= g;
    }
}

void add(Fraction *res, long long p, long long q) {
    res->num = res->num * q + p * res->den;
    res->den = res->den * q;
    reduce(res);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = {0, 1};
    for (int i = 0; i < n; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        add(&sum, p, q);
    }
    
    if (sum.den == 0) sum.den = 1;
    if (sum.num == 0) {
        printf("0 1\n");
    } else {
        printf("%lld %lld\n", sum.num, sum.den);
    }
    
    return 0;
}
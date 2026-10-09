#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int64_t num;
    int64_t den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return; // Should not happen
    if (f->num == 0) {
        f->num = 0;
        f->den = 1;
        return;
    }
    int64_t g = f->num > 0 ? f->num : -f->num;
    for (int64_t d = 2; d * d <= g; d++) {
        if (g % d == 0 && f->den % d == 0) {
            while (g % d == 0 && f->den % d == 0) {
                g /= d;
                f->den /= d;
            }
        }
    }
    if (f->num < 0) {
        f->den = -f->den;
        f->num = -f->num;
    }
}

void add(Fraction *a, Fraction *b) {
    int64_t num = a->num * b->den + b->num * a->den;
    int64_t den = a->den * b->den;
    a->num = num;
    a->den = den;
    reduce(a);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = {0, 1};
    
    for (int i = 0; i < n; i++) {
        int64_t p, q;
        scanf("%lld%lld", &p, &q);
        Fraction frac = {p, q};
        add(&sum, &frac);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
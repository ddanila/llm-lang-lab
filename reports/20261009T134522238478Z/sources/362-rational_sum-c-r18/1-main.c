#include <stdio.h>
#include <stdint.h>

typedef struct {
    int64_t num;
    int64_t den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return;
    int64_t g = f->num > 0 ? f->num : -f->num;
    if (g == 0) {
        f->num = 0;
        f->den = 1;
        return;
    }
    int64_t a = f->num, b = f->den;
    while (b != 0) {
        int64_t t = a % b;
        a = b;
        b = t;
    }
    int64_t gcd = a;
    f->num /= gcd;
    f->den /= gcd;
    if (f->den < 0) {
        f->den = -f->den;
        f->num = -f->num;
    }
}

Fraction add(Fraction a, Fraction b) {
    Fraction r;
    r.num = a.num * b.den + b.num * a.den;
    r.den = a.den * b.den;
    reduce(&r);
    return r;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    Fraction sum = {0, 1};
    for (int i = 0; i < N; i++) {
        int64_t p, q;
        scanf("%lld%lld", &p, &q);
        Fraction f = {p, q};
        sum = add(sum, f);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    return 0;
}
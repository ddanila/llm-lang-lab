#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return;
    if (f->num == 0) {
        f->num = 0;
        f->den = 1;
        return;
    }
    long long g = f->num > 0 ? f->num : -f->num;
    for (long long d = 2; d * d <= g; ++d) {
        if (g % d == 0 && (f->den % d == 0)) {
            while (g % d == 0 && (f->den % d == 0)) {
                g /= d;
                f->den /= d;
            }
        }
    }
    long long common = 1;
    for (long long d = 2; d * d <= g; ++d) {
        if (g % d == 0 && (f->den % d == 0)) {
            while (g % d == 0 && (f->den % d == 0)) {
                common *= d;
                g /= d;
                f->den /= d;
            }
        }
    }
    if (common > 1) {
        f->num /= common;
        f->den /= common;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = {0, 1};
    
    for (int i = 0; i < n; ++i) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        
        Fraction term = {p, q};
        reduce(&term);
        
        long long new_num = sum.num * term.den + sum.den * term.num;
        long long new_den = sum.den * term.den;
        
        sum.num = new_num;
        sum.den = new_den;
        
        reduce(&sum);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
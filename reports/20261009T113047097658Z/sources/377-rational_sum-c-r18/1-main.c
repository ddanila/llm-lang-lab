#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int64_t num;
    int64_t den;
} Fraction;

void reduce(Fraction *f) {
    if (f->den == 0) return;
    int64_t g = f->num > 0 ? f->num : -f->num;
    if (g == 0) {
        f->den = 1;
        return;
    }
    for (int64_t d = 2; d * d <= g && d <= f->den; ++d) {
        while (f->num % d == 0 && f->den % d == 0) {
            f->num /= d;
            f->den /= d;
        }
    }
    if (f->num < 0) {
        f->num = -f->num;
        f->den = -f->den;
    } else if (f->den < 0) {
        f->num = -f->num;
        f->den = -f->den;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    Fraction sum = {0, 1};
    
    for (int i = 0; i < n; ++i) {
        int64_t p, q;
        scanf("%lld %lld", &p, &q);
        
        Fraction f = {p, q};
        reduce(&f);
        
        // sum = sum + f
        int64_t new_num = sum.num * f.den + f.num * sum.den;
        int64_t new_den = sum.den * f.den;
        
        sum.num = new_num;
        sum.den = new_den;
        
        reduce(&sum);
    }
    
    printf("%lld %lld\n", sum.num, sum.den);
    
    return 0;
}
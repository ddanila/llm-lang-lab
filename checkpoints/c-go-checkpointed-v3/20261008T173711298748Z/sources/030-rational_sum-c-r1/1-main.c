#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

Fraction add_fractions(Fraction a, Fraction b) {
    Fraction res;
    res.num = a.num * b.den + b.num * a.den;
    res.den = a.den * b.den;
    return res;
}

void reduce_fraction(Fraction *f) {
    if (f->num == 0) {
        f->den = 1;
        return;
    }
    long long g = 1;
    long long abs_num = f->num < 0 ? -f->num : f->num;
    long long abs_den = f->den;

    for (long long i = 2; i * i <= abs_num && i * i <= abs_den; i++) {
        while (abs_num % i == 0) abs_num /= i;
        while (abs_den % i == 0) abs_den /= i;
    }

    if (abs_num > 1 || abs_den > 1) {
        long long min_val = abs_num < abs_den ? abs_num : abs_den;
        long long max_val = abs_num > abs_den ? abs_num : abs_den;
        g = 1;
        for (long long i = 2; i * i <= min_val; i++) {
            while (min_val % i == 0) {
                if (max_val % i == 0) {
                    g *= i;
                    min_val /= i;
                    max_val /= i;
                } else {
                    break;
                }
            }
        }
        if (g == 1 && min_val > 1 && min_val == max_val) {
            g = min_val;
        } else if (min_val > 1 && min_val != max_val) {
            // Check if remaining parts are equal
            long long common = min_val;
            while (common > 1) {
                common--;
                if (abs_num % common == 0 && abs_den % common == 0) {
                    g *= common;
                    break;
                }
            }
        }
    }

    f->num /= g;
    f->den /= g;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Fraction sum = {0, 1};

    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        Fraction frac = {p, q};
        sum = add_fractions(sum, frac);
        reduce_fraction(&sum);
    }

    printf("%lld %lld\n", sum.num, sum.den);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef long long int64;

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int64 num = 0;
    int64 den = 1;

    for (int i = 0; i < N; i++) {
        int64 p, q;
        scanf("%lld %lld", &p, &q);

        // Add p/q to num/den: new numerator = num*q + p*den
        // new denominator = den*q
        // Then reduce by GCD
        
        int64 new_num = num * q + p * den;
        int64 new_den = den * q;

        int64 gcd_val = (new_num == 0) ? 1 : new_den > 0 ? new_den < 0 ? -new_den : new_den : 1; // abs(new_den)
        if (gcd_val < 0) gcd_val = -gcd_val;

        int64 common = 0;
        int64 a = new_num, b = new_den;
        while (b != 0) {
            int64 t = a % b;
            a = b;
            b = t;
        }
        common = (a < 0) ? -a : a;

        num = new_num / common;
        den = new_den / common;

        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

    printf("%lld %lld\n", num, den);

    return 0;
}
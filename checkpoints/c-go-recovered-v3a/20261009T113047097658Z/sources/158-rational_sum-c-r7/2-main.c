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
        if (scanf("%lld%lld", &p, &q) != 2) break;

        // Add p/q to num/den: new_num = num*q + p*den, new_den = den*q
        int64 new_num = num * q + p * den;
        int64 new_den = den * q;

        // Reduce by gcd
        if (new_den == 0) continue;
        
        int64 a = new_num;
        int64 b = new_den;
        
        int64 g = 1;
        if (a != 0 && b != 0) {
            int64 x = a < 0 ? -a : a;
            int64 y = b < 0 ? -b : b;
            while (y != 0) {
                int64 t = x % y;
                x = y;
                y = t;
            }
            g = x;
        }

        num = new_num / g;
        den = new_den / g;
    }

    // Ensure positive denominator
    if (den < 0) {
        num = -num;
        den = -den;
    }

    printf("%lld %lld\n", num, den);
    return 0;
}
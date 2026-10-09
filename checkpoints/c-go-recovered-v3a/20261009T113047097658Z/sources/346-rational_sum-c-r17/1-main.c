#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef long long int64;

int gcd(int64 a, int64 b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b != 0) {
        int64 t = b;
        b = a % b;
        a = t;
    }
    return (int)(a > 0 ? a : -a);
}

void reduce(int64 *p, int64 *q) {
    if (*q == 0) return;
    int g = gcd(*p, *q);
    *p /= g;
    *q /= g;
    if (*q < 0) {
        *p = -*p;
        *q = -*q;
    }
}

int parse_long(long long *val, char **ptr) {
    char *end;
    errno = 0;
    char *s = *ptr;
    if (*s == '\0' || isspace((unsigned char)*s)) {
        while (isspace((unsigned char)*s)) s++;
        if (*s == '\0') return 0;
    }
    long long n = strtoll(s, &end, 10);
    if (errno != 0 || end == s) return -1;
    *val = n;
    *ptr = end;
    return 0;
}

int main(void) {
    char buf[65536];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    buf[len] = '\0';

    char *p = buf;
    
    long long N;
    if (parse_long(&N, &p) != 0) return 1;

    int64 num = 0;
    int64 den = 1;

    for (long long i = 0; i < N; i++) {
        long long p_val, q_val;
        if (parse_long(&p_val, &p) != 0 || parse_long(&q_val, &p) != 0) return 1;

        int64 num_new = p_val;
        int64 den_new = q_val;

        // Add: num/den + num_new/den_new = (num*den_new + num_new*den) / (den*den_new)
        int64 new_num = num * den_new + num_new * den;
        int64 new_den = den * den_new;

        reduce(&new_num, &new_den);
        num = new_num;
        den = new_den;
    }

    printf("%lld %lld\n", num, den);

    return 0;
}
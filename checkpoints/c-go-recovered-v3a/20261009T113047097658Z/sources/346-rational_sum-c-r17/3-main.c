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

int main(void) {
    char buf[65536];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    buf[len] = '\0';

    char *s = buf;
    
    // Read N
    while (isspace((unsigned char)*s)) s++;
    if (!isdigit((unsigned char)*s) && *s != '-') return 1;
    char *end = s + 1;
    while (*end != '\0' && isdigit((unsigned char)*end)) end++;
    
    long long N = strtoll(s, &end, 10);

    int64 num = 0;
    int64 den = 1;

    for (long long i = 0; i < N; i++) {
        // Read p
        while (isspace((unsigned char)*s)) s++;
        if (!isdigit((unsigned char)*s) && *s != '-') return 1;
        
        char *p_start = s;
        char *p_end = s + 1;
        while (*p_end != '\0' && isdigit((unsigned char)*p_end)) p_end++;
        
        long long p_val = strtoll(p_start, &p_end, 10);
        
        // Read q
        while (isspace((unsigned char)*s)) s++;
        if (!isdigit((unsigned char)*s) && *s != '-') return 1;
        
        char *q_start = s;
        char *q_end = s + 1;
        while (*q_end != '\0' && isdigit((unsigned char)*q_end)) q_end++;
        
        long long q_val = strtoll(q_start, &q_end, 10);

        int64 num_new = p_val;
        int64 den_new = q_val;

        // Add: num/den + num_new/den_new = (num*den_new + num_new*den) / (den*den_new)
        int64 new_num = num * den_new + num_new * den;
        int64 new_den = den * den_new;

        reduce(&new_num, &new_den);
        num = new_num;
        den = new_den;
        
        s = q_end;
    }

    printf("%lld %lld\n", num, den);

    return 0;
}
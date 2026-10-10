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

    char *p = buf;
    
    long long N;
    if (len == 0 || !isdigit((unsigned char)*p)) return 1;
    
    while (isspace((unsigned char)*p)) p++;
    
    for (; *p != '\0' && !isdigit((unsigned char)*p) && *p != '-'; p++);
    long long start = p - buf;
    char *end = p + 1;
    while (*end != '\0' && isdigit((unsigned char)*end)) end++;
    
    char temp[65536];
    strncpy(temp, buf, len);
    temp[len] = '\0';
    
    char *s = temp;
    while (isspace((unsigned char)*s)) s++;
    long long val = strtoll(s, &end, 10);
    N = val;

    int64 num = 0;
    int64 den = 1;

    for (long long i = 0; i < N; i++) {
        char *pos = s;
        while (isspace((unsigned char)*pos)) pos++;
        
        // Read p
        if (!isdigit((unsigned char)*pos) && *pos != '-') {
            return 1;
        }
        long long start_p = pos - temp;
        char *end_p = pos + 1;
        while (*end_p != '\0' && isdigit((unsigned char)*end_p)) end_p++;
        
        long long p_val = strtoll(pos, &end_p, 10);
        s = end_p;
        
        // Read q
        if (!isdigit((unsigned char)*s) && *s != '-') {
            return 1;
        }
        long long start_q = s - temp;
        char *end_q = s + 1;
        while (*end_q != '\0' && isdigit((unsigned char)*end_q)) end_q++;
        
        long long q_val = strtoll(s, &end_q, 10);

        int64 num_new = p_val;
        int64 den_new = q_val;

        // Add: num/den + num_new/den_new = (num*den_new + num_new*den) / (den*den_new)
        int64 new_num = num * den_new + num_new * den;
        int64 new_den = den * den_new;

        reduce(&new_num, &new_den);
        num = new_num;
        den = new_den;
        
        s = end_q;
    }

    printf("%lld %lld\n", num, den);

    return 0;
}
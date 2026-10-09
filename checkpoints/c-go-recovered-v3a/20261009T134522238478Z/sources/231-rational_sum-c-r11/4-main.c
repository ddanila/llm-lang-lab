#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef long long int64;

int gcd(int64 a, int64 b) {
    while (b != 0) {
        int64 t = b;
        b = a % b;
        a = t;
    }
    return a > 0 ? a : -a;
}

void reduce(int64 *n, int64 *d) {
    if (*d == 0) {
        *n = 0;
        *d = 1;
        return;
    }
    int64 g = gcd(*n, *d);
    *n /= g;
    *d /= g;
    if (*d < 0) {
        *n = -(*n);
        *d = -(*d);
    }
}

int main(void) {
    char buf[1024];
    int pos = 0;
    
    while (pos < (int)sizeof(buf)) {
        int c = getchar();
        if (c == EOF) break;
        if (!isspace(c)) {
            buf[pos++] = (char)c;
        } else {
            break;
        }
    }
    buf[pos] = '\0';
    
    if (pos == 0) return 0;

    char *endptr;
    int N = strtol(buf, &endptr, 10);
    
    int64 sum_n = 0;
    int64 sum_d = 1;
    
    for (int i = 0; i < N; i++) {
        while ((char)isspace(getchar()) != '\0');
        
        endptr = buf;
        int64 p = strtol(buf, &endptr, 10);
        
        while ((char)isspace(getchar()) != '\0');
        endptr = buf;
        int64 q = strtol(buf, &endptr, 10);
        
        int64 new_n = p * sum_d;
        int64 new_d = sum_d * q;
        
        reduce(&new_n, &new_d);
        
        int64 combined_n = new_n + sum_n;
        int64 combined_d = new_d;
        
        reduce(&combined_n, &combined_d);
        
        sum_n = combined_n;
        sum_d = combined_d;
    }
    
    printf("%lld %lld\n", sum_n, sum_d);
    
    return 0;
}
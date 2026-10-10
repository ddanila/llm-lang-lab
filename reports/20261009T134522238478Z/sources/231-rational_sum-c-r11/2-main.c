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
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 0;
    }

    int N = atoi(buf);
    
    int64 sum_n = 0;
    int64 sum_d = 1;
    
    for (int i = 0; i < N; i++) {
        int ch;
        while ((ch = getchar()) != EOF && isspace(ch));
        
        char *endptr;
        int64 p = strtol(&buf[0], &endptr, 10);
        
        while ((ch = getchar()) != EOF && isspace(ch));
        int64 q = strtol(&buf[0], &endptr, 10);
    }
    
    return 0;
}
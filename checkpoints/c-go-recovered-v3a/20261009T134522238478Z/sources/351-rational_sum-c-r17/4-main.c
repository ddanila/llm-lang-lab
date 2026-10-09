#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int64;

int64 gcd(int64 a, int64 b) {
    return b == 0 ? a : gcd(b, a % b);
}

void reduce(int64 *num, int64 *den) {
    if (*num == 0) {
        *den = 1;
        return;
    }
    int64 g = gcd(*num, *den);
    *num /= g;
    *den /= g;
    if (*den < 0) {
        *num = -*num;
        *den = -*den;
    }
}

int main(void) {
    char buf[1 << 20];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    if (len == 0) return 0;
    
    int idx = 0;
    
    // Skip N (first number)
    while (idx < len && buf[idx] != ' ' && buf[idx] != '\n') {
        idx++;
    }
    
    int64 num = 0;
    int64 den = 1;
    
    // Parse N pairs
    for (int i = 0; i < 20; i++) {
        char c = buf[idx];
        
        if (c == ' ') {
            idx++;
            continue;
        }
        if (c == '\n') break;
        
        // Parse numerator p
        int64 p = 0;
        int neg = 0;
        while (idx < len) {
            char ch = buf[idx];
            if (ch == '-' || ch >= '0' && ch <= '9') {
                if (ch == '-') neg = 1;
                else p = p * 10 + (ch - '0');
                idx++;
            } else {
                break;
            }
        }
        if (neg) p = -p;
        
        // Parse denominator q
        int64 q = 0;
        while (idx < len) {
            char ch = buf[idx];
            if (ch >= '0' && ch <= '9') {
                q = q * 10 + (ch - '0');
                idx++;
            } else {
                break;
            }
        }
        
        // Add p/q to num/den
        int64 new_num = num * q + den * p;
        int64 new_den = den * q;
        reduce(&new_num, &new_den);
        num = new_num;
        den = new_den;
    }
    
    printf("%lld %lld\n", num, den);
    return 0;
}
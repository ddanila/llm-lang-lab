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
    int64 g = gcd(*num != 0 ? *num : -1, *den != 0 ? *den : 1);
    if (g != 0) {
        *num /= g;
        *den /= g;
    }
    if (*den < 0) {
        *num = -*num;
        *den = -*den;
    }
}

int main(void) {
    char buf[1 << 20];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    if (len == 0) return 0;
    
    int64 num = 0;
    int64 den = 1;
    int n = 0;
    
    int idx = 0;
    while (idx < len && buf[idx] != '\n') {
        if (buf[idx] == '-' || buf[idx] >= '0' && buf[idx] <= '9') {
            int64 val = 0;
            int neg = 0;
            while (idx < len) {
                char c = buf[idx];
                if (c == '-') {
                    neg = 1;
                    idx++;
                } else if (c >= '0' && c <= '9') {
                    val = val * 10 + (c - '0');
                    idx++;
                } else {
                    break;
                }
            }
            if (neg) val = -val;
            
            int64 dval = 0;
            idx++;
            while (idx < len) {
                char c = buf[idx];
                if (c >= '0' && c <= '9') {
                    dval = dval * 10 + (c - '0');
                    idx++;
                } else {
                    break;
                }
            }
            
            // Add val/dval to num/den
            int64 new_num = num * dval + den * val;
            int64 new_den = den * dval;
            reduce(&new_num, &new_den);
            num = new_num;
            den = new_den;
        } else {
            idx++;
        }
    }
    
    printf("%lld %lld\n", num, den);
    return 0;
}
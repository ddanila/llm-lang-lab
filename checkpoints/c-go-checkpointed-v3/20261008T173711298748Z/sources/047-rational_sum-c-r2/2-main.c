#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long num;
    long long den;
} Fraction;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    Fraction sum = {0, 1};
    
    for (int i = 0; i < N; i++) {
        long long p, q;
        scanf("%lld %lld", &p, &q);
        
        if (i == 0) {
            sum.num = p;
            sum.den = q;
        } else {
            long long new_num = sum.num * q + p * sum.den;
            long long new_den = sum.den * q;
            
            if (new_den < 0) {
                new_num = -new_num;
                new_den = -new_den;
            }
            
            long long gcd_val = gcd(abs(new_num), abs(new_den));
            sum.num = new_num / gcd_val;
            sum.den = new_den / gcd_val;
        }
    }
    
    if (sum.num == 0 && sum.den == 1) {
        printf("0 1\n");
    } else {
        printf("%lld %lld\n", sum.num, sum.den);
    }
    
    return 0;
}
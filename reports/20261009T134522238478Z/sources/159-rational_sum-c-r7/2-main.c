#include <stdio.h>
#include <stdlib.h>

typedef long long int64;

void reduce(int64 *num, int64 *den) {
    if (*den == 0) return;
    int64 g = 1;
    for (int64 a = 2; a * a <= abs(*den); a++) {
        while ((*num % a == 0) && (*den % a == 0)) {
            *num /= a;
            *den /= a;
        }
    }
    if (*den < 0) {
        *num = -*num;
        *den = -*den;
    }
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    int64 num = 0, den = 1;
    
    for (int i = 0; i < N; i++) {
        int64 p, q;
        scanf("%lld %lld", &p, &q);
        
        // Add p/q to num/den: new_num = num*q + p*den
        // new_den = den*q
        int64 new_num = num * q + p * den;
        int64 new_den = den * q;
        
        num = new_num;
        den = new_den;
        
        reduce(&num, &den);
    }
    
    printf("%lld %lld\n", num, den);
    
    return 0;
}
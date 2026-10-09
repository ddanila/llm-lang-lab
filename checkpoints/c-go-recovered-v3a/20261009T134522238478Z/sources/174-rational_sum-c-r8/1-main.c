#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

void reduce(ll *n, ll *d) {
    if (*d == 0) return;
    ll g = (ll)(*n > 0 ? *n : -*n);
    while (g > 1) {
        if ((*n % g != 0) || (*d % g != 0)) {
            g--;
            continue;
        }
        *n /= g;
        *d /= g;
        if (*n == 0) break;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    ll num = 0, den = 1;
    
    for (int i = 0; i < n; i++) {
        ll p, q;
        scanf("%lld %lld", &p, &q);
        
        // Add p/q to num/den: new_num = num*q + p*den, new_den = den*q
        ll new_num = num * q + p * den;
        ll new_den = den * q;
        
        reduce(&new_num, &new_den);
        
        num = new_num;
        den = new_den;
    }
    
    // Ensure positive denominator
    if (den < 0) {
        den = -den;
        num = -num;
    }
    
    printf("%lld %lld\n", num, den);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll gcd(ll a, ll b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b != 0) {
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void reduce(ll *n, ll *d) {
    if (*d == 0) return;
    ll g = gcd(*n, *d);
    *n /= g;
    *d /= g;
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
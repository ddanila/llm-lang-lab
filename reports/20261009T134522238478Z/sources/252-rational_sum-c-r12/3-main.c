#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll gcd(ll a, ll b) {
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main(void) {
    ll N, p, q;
    
    if (scanf("%lld", &N) != 1) {
        printf("0 1\n");
        return 0;
    }
    
    ll num = 0;
    ll den = 1;
    
    for (ll i = 0; i < N; i++) {
        scanf("%lld %lld", &p, &q);
        
        // Add fractions: num/den + p/q = (num*q + p*den)/(den*q)
        ll new_num = num * q + p * den;
        ll new_den = den * q;
        
        // Reduce the result
        ll g3 = gcd(new_num, new_den);
        new_num /= g3;
        new_den /= g3;
        
        num = new_num;
        den = new_den;
    }
    
    if (den < 0) {
        num = -num;
        den = -den;
    }
    
    printf("%lld %lld\n", num, den);
    
    return 0;
}
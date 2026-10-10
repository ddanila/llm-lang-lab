#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    char buf[1024];
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;
    
    ll N;
    int pos = 0;
    while (pos < (int)strlen(buf) && isspace((unsigned char)buf[pos])) pos++;
    if (pos >= (int)strlen(buf)) {
        printf("0 1\n");
        return 0;
    }
    
    char *endptr;
    N = strtoll(&buf[pos], &endptr, 10);
    pos = (int)(endptr - buf);
    while (pos < (int)strlen(buf) && isspace((unsigned char)buf[pos])) pos++;
    
    ll num = 0;
    ll den = 1;
    
    for (ll i = 0; i < N; i++) {
        while (pos < (int)strlen(buf) && isspace((unsigned char)buf[pos])) pos++;
        if (pos >= (int)strlen(buf)) break;
        
        ll p = strtoll(&buf[pos], &endptr, 10);
        pos = (int)(endptr - buf);
        while (pos < (int)strlen(buf) && isspace((unsigned char)buf[pos])) pos++;
        
        ll q = strtoll(&buf[pos], &endptr, 10);
        pos = (int)(endptr - buf);
        
        ll g = gcd(p, q);
        p /= g;
        q /= g;
        
        // Reduce existing fraction first
        ll g2 = gcd(num, den);
        num /= g2;
        den /= g2;
        
        // Cross-multiply to add: (num/den) + (p/q) = (num*q + p*den) / (den*q)
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
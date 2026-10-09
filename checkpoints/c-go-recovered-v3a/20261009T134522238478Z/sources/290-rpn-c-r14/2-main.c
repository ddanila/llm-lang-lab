#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK 256

long long stack[MAX_STACK];
int sp = 0;

int parse_token(const char *s, long long *val) {
    if (s[0] == '\0') return -1;
    
    const char *p = s;
    int neg = 0;
    
    if (*p == '+' || *p == '-') {
        if (*p == '-') neg = 1;
        p++;
        if (*p == '\0') return -1;
    }
    
    while (*p && !isspace((unsigned char)*p)) {
        if (!isdigit((unsigned char)*p)) return -1;
        *val *= 10;
        *val += *p - '0';
        p++;
    }
    
    if (p == s) return -1;
    
    *val = neg ? -*val : *val;
    return 0;
}

int main(void) {
    char buf[65536];
    fgets(buf, sizeof(buf), stdin);
    
    const char *p = buf;
    while (*p && (unsigned char)*p < 128) {
        if (isspace((unsigned char)*p)) p++;
        else {
            char tok[64];
            int len = 0;
            while (*p && !isspace((unsigned char)*p) && len < 63) {
                tok[len++] = *p++;
            }
            tok[len] = '\0';
            
            if (len == 0) continue;
            
            if (tok[0] == '+' || tok[0] == '-' || tok[0] == '*') {
                // operator
                if (sp < 2) {
                    printf("ERROR\n");
                    return 0;
                }
                
                long long b = stack[sp-1];
                long long a = stack[sp-2];
                sp--;
                stack[sp] = a;
                sp--;
                stack[sp] = b;
                
                if (tok[0] == '+') {
                    stack[sp] = stack[sp] + stack[sp+1];
                } else if (tok[0] == '-') {
                    stack[sp] = stack[sp] - stack[sp+1];
                } else if (tok[0] == '*') {
                    stack[sp] = stack[sp] * stack[sp+1];
                }
            } else {
                // number
                long long val;
                if (parse_token(tok, &val) != 0) {
                    printf("ERROR\n");
                    return 0;
                }
                
                if (sp >= MAX_STACK - 1) {
                    printf("ERROR\n");
                    return 0;
                }
                
                stack[sp++] = val;
            }
        }
    }
    
    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
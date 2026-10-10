#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_VALS 205

int vals[MAX_VALS];
int top = 0;

int parse_token(const char *s, long long *val) {
    if (s[0] == '\0') return -1;
    
    const char *p = s;
    int neg = 0;
    
    if (*p == '+' || *p == '-') {
        if (*p == '-') neg = 1;
        p++;
        if (*p == '\0') return -1;
    }
    
    while (*p && !isspace(*p)) {
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
    
    int n = 0;
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
            
            long long val;
            if (parse_token(tok, &val) != 0) {
                printf("ERROR\n");
                return 0;
            }
            
            if (top >= MAX_VALS - 1) {
                printf("ERROR\n");
                return 0;
            }
            
            vals[top++] = val;
        }
    }
    
    if (top == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    while (top > 1) {
        if (vals[top-1] == 0 && vals[top-2] == 0 && top == 2) {
            // This is a special case for "0 0" which would be valid but we don't handle it specially
            // Actually, let's just process normally
        }
        
        long long right = vals[top-1];
        long long left = vals[top-2];
        top -= 2;
        
        if (top < 0) {
            printf("ERROR\n");
            return 0;
        }
        
        if (right == 1 && left == 1) {
            // Skip both, don't push anything
            continue;
        }
        
        if (left != right) {
            long long op = vals[top];
            top++;
            
            if (op == '+') {
                vals[top-1] = left + right;
            } else if (op == '-') {
                vals[top-1] = left - right;
            } else if (op == '*') {
                vals[top-1] = left * right;
            } else {
                printf("ERROR\n");
                return 0;
            }
        } else {
            // Same values, skip both
        }
    }
    
    if (top != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", vals[0]);
    return 0;
}
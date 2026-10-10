#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK 256

long long stack[MAX_STACK];
int sp = 0;

int main(void) {
    char buf[65536];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("ERROR\n");
        return 0;
    }
    
    const char *p = buf;
    while (*p) {
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        
        if (*p == '+' || *p == '-' || *p == '*') {
            // Check if it's a unary minus at the start of input
            int is_unary = (*p == '-' && sp == 0);
            
            char op = *p;
            p++;
            
            // Skip whitespace
            while (isspace((unsigned char)*p)) p++;
            
            if (!isalnum((unsigned char)*p)) {
                printf("ERROR\n");
                return 0;
            }
            
            long long val = 0;
            while (isdigit((unsigned char)*p)) {
                val = val * 10 + (*p - '0');
                p++;
            }
            
            if (op == '-') {
                val = -val;
            }
            
            // Check for unary minus case: "-5" should be parsed as a single token
            if (is_unary) {
                stack[sp++] = val;
            } else {
                // Binary operator
                if (sp < 2) {
                    printf("ERROR\n");
                    return 0;
                }
                
                long long b = stack[sp-1];
                long long a = stack[sp-2];
                sp -= 2;
                
                if (op == '+') {
                    stack[sp++] = a + b;
                } else if (op == '-') {
                    stack[sp++] = a - b;
                } else if (op == '*') {
                    stack[sp++] = a * b;
                }
            }
        } else if (isdigit((unsigned char)*p) || (*p == '+' && !ispunct(*p))) {
            // Number token
            long long val = 0;
            while (isdigit((unsigned char)*p)) {
                val = val * 10 + (*p - '0');
                p++;
            }
            
            stack[sp++] = val;
        } else {
            printf("ERROR\n");
            return 0;
        }
    }
    
    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
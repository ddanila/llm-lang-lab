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
        
        // Check for operator or number start
        int is_op_start = (*p == '+' || *p == '-' || *p == '*');
        int is_num_start = isdigit((unsigned char)*p) || (*p == '+');
        
        if (is_op_start || is_num_start) {
            char op = *p;
            p++;
            
            // Skip whitespace after operator sign if it's not a unary minus
            if (op != '-' || sp > 0) {
                while (isspace((unsigned char)*p)) p++;
            }
            
            long long val = 0;
            int has_digits = 0;
            
            while (isdigit((unsigned char)*p)) {
                has_digits = 1;
                val = val * 10 + (*p - '0');
                p++;
            }
            
            if (!has_digits) {
                printf("ERROR\n");
                return 0;
            }
            
            // Handle unary minus at start of input
            if (op == '-' && sp == 0) {
                val = -val;
            } else if (op == '+' || op == '*') {
                // Binary operator - need to check it's not a number starting with +
                if (sp < 2) {
                    printf("ERROR\n");
                    return 0;
                }
                
                long long b = stack[sp-1];
                long long a = stack[sp-2];
                sp -= 2;
                
                if (op == '+') {
                    stack[sp++] = a + b;
                } else if (op == '*') {
                    stack[sp++] = a * b;
                } else if (op == '-') {
                    // Check if this was unary minus
                    int was_unary = (op == '-' && sp == 0);
                    if (!was_unary) {
                        stack[sp++] = a - b;
                    } else {
                        stack[sp++] = val;
                    }
                }
            } else if (op == '+') {
                // Binary plus operator
                if (sp < 2) {
                    printf("ERROR\n");
                    return 0;
                }
                
                long long b = stack[sp-1];
                long long a = stack[sp-2];
                sp -= 2;
                
                stack[sp++] = a + b;
            } else {
                // Number token (possibly starting with +)
                if (op == '+' && val > 0) {
                    // It was "+5" which is just the number 5
                    stack[sp++] = val;
                } else {
                    stack[sp++] = val;
                }
            }
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
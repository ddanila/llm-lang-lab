#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int main(void) {
    char *tokens[200];
    int token_count = 0;
    char buffer[65536];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("ERROR\n");
        return 0;
    }
    
    char *p = buffer;
    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        
        char *start = p;
        
        if (*p == '+' || *p == '-' || *p == '*') {
            tokens[token_count++] = start;
            while (*p && !isspace((unsigned char)*p)) p++;
        } else {
            if (!isdigit((unsigned char)*p) && *p != '+' && *p != '-') {
                printf("ERROR\n");
                return 0;
            }
            tokens[token_count++] = start;
            while (*p && !isspace((unsigned char)*p)) p++;
        }
    }
    
    if (token_count == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    long long *stack = malloc(200 * sizeof(long long));
    int top = 0;
    
    for (int i = 0; i < token_count; i++) {
        char *tok = tokens[i];
        
        if (*tok == '+' || *tok == '-' || *tok == '*') {
            if (top < 2) {
                free(stack);
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[top - 1];
            long long a = stack[top - 2];
            top -= 2;
            
            switch (*tok) {
                case '+':
                    stack[top++] = a + b;
                    break;
                case '-':
                    stack[top++] = a - b;
                    break;
                case '*':
                    stack[top++] = a * b;
                    break;
            }
        } else {
            char *endptr;
            long long val;
            
            if (*tok == '+' || *tok == '-') {
                int sign = 1;
                if (*tok == '-') {
                    sign = -1;
                    tok++;
                }
                
                // Check for empty string after optional sign
                if (*tok == '\0') {
                    free(stack);
                    printf("ERROR\n");
                    return 0;
                }
                
                val = strtoll(tok, &endptr, 10);
                val *= sign;
            } else {
                val = strtoll(tok, &endptr, 10);
            }
            
            if (*endptr != '\0') {
                free(stack);
                printf("ERROR\n");
                return 0;
            }
            
            stack[top++] = val;
        }
    }
    
    free(stack);
    
    if (top != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    
    return 0;
}
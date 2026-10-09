#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_TOKENS 200
#define STACK_SIZE 256

int main(void) {
    char buf[MAX_TOKENS][128];
    int count = 0;
    
    // Read all input into a buffer first
    char input[1024 * 200];
    size_t in_len = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (in_len < sizeof(input) - 1) {
            input[in_len++] = (char)c;
        }
    }
    input[in_len] = '\0';
    
    // Parse tokens
    char *p = input;
    int idx = 0;
    while (*p && idx < MAX_TOKENS) {
        if (isspace((unsigned char)*p)) {
            p++;
        } else {
            // Copy token until whitespace or end
            size_t len = 0;
            while (*p && !isspace((unsigned char)*p) && len < sizeof(buf[idx]) - 1) {
                buf[idx][len++] = *p++;
            }
            buf[idx][len] = '\0';
            idx++;
        }
    }
    
    count = idx;
    
    if (count == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    // Stack for RPN evaluation
    long long stack[STACK_SIZE];
    int sp = 0; // stack pointer
    
    for (int i = 0; i < count; i++) {
        const char *token = buf[i];
        
        if (strlen(token) == 0) continue;
        
        // Check if operator
        if (*token == '+' || *token == '-' || *token == '*') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            
            long long right = stack[sp - 1];
            long long left = stack[sp - 2];
            sp -= 2;
            
            if (*token == '+') {
                stack[++sp - 1] = left + right;
            } else if (*token == '-') {
                stack[++sp - 1] = left - right;
            } else if (*token == '*') {
                stack[++sp - 1] = left * right;
            }
        } else {
            // Must be integer
            char *endptr;
            long long val = strtoll(token, &endptr, 10);
            
            // Check for invalid characters or no digits
            if (*token == '+' || *token == '-') {
                // Leading sign is OK, but must have at least one digit after
                char *p2 = token + 1;
                if (strlen(p2) == 0 || !isdigit((unsigned char)*p2)) {
                    printf("ERROR\n");
                    return 0;
                }
            } else if (*token == '\0') {
                // Empty token - shouldn't happen with our parsing
                printf("ERROR\n");
                return 0;
            }
            
            stack[sp++] = val;
        }
    }
    
    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
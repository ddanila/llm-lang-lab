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
        
        // Check if this is an operator or a negative/positive number
        // If it starts with + or -, check if there's at least one digit after
        int is_operator = 0;
        if (*tok == '+' || *tok == '*' || *tok == '-') {
            // For +, *, and - (unary), they are operators
            // But for -, if followed by a digit, it's part of a negative number
            // Actually, let's think about this differently:
            // +, *, and - at the start are potential operators
            // But - can also be part of a negative number like "-5"
            // The spec says tokens are separated by whitespace, so "-5" is one token
            // We need to check if it's just "+" or "*" (always operators) 
            // or "-" followed by digits (negative number) or just "-" (invalid operator without operands)
            
            if (*tok == '+' || *tok == '*') {
                is_operator = 1;
            } else if (*tok == '-') {
                // Check if it's a negative number (has digits after -)
                if (tok[1] != '\0' && isdigit((unsigned char)tok[1])) {
                    // It's a negative number, not an operator
                    is_operator = 0;
                } else {
                    // Just "-" or "- " followed by something invalid
                    // This would be treated as an operator (subtraction)
                    is_operator = 1;
                }
            }
        }
        
        if (is_operator) {
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
            
            // Parse as integer (handles optional leading + or -)
            val = strtoll(tok, &endptr, 10);
            
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

int main(void) {
    char tokens[MAX_TOKENS][64];
    int token_count = 0;
    
    // Read all tokens from stdin
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        char *token = strtok(buffer, " \t\n\r");
        if (token == NULL) break;
        
        // Check for empty token (shouldn't happen with fgets and strtok on non-empty line)
        int len = 0;
        while (token[len] != '\0' && token[len] != '\n' && token[len] != ' ' && token[len] != '\t') {
            if (len < MAX_TOKENS - 1) {
                tokens[token_count][len] = token[len];
                len++;
            } else {
                // Token too long, treat as invalid
                break;
            }
        }
        tokens[token_count][len] = '\0';
        token_count++;
    }
    
    if (token_count == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    // Stack implementation
    int64_t stack[STACK_SIZE];
    int top = -1; // Empty stack
    
    for (int i = 0; i < token_count; i++) {
        const char *tok = tokens[i];
        int len = strlen(tok);
        
        if (len == 0) {
            printf("ERROR\n");
            return 0;
        }
        
        // Check for operator
        if (*tok == '+' || *tok == '-' || *tok == '*') {
            // Pop two operands
            if (top < 1) {
                printf("ERROR\n");
                return 0;
            }
            int64_t right = stack[top--];
            int64_t left = stack[top--];
            
            char op = *tok;
            int64_t result;
            
            if (op == '+') {
                result = left + right;
            } else if (op == '-') {
                result = left - right;
            } else if (op == '*') {
                result = left * right;
            } else {
                printf("ERROR\n");
                return 0;
            }
            
            // Check for overflow
            if (result > INT64_MAX || result < INT64_MIN) {
                printf("ERROR\n");
                return 0;
            }
            
            stack[++top] = result;
        } else {
            // Must be an integer
            int is_negative = (*tok == '-');
            const char *num = tok + (is_negative ? 1 : 0);
            int num_len = len - (is_negative ? 1 : 0);
            
            if (num_len == 0) {
                // No digits after sign
                printf("ERROR\n");
                return 0;
            }
            
            // Check for leading + without digits
            if (*tok == '+' && num_len == 0) {
                printf("ERROR\n");
                return 0;
            }
            
            int64_t val = 0;
            for (int j = 0; j < num_len; j++) {
                char c = num[j];
                if (!isdigit((unsigned char)c)) {
                    printf("ERROR\n");
                    return 0;
                }
                val = val * 10 + (c - '0');
            }
            
            if (is_negative) {
                val = -val;
            }
            
            // Check for overflow
            if (val > INT64_MAX || val < INT64_MIN) {
                printf("ERROR\n");
                return 0;
            }
            
            stack[++top] = val;
        }
    }
    
    if (top != 0) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

typedef long long int64;

int main(void) {
    char buffer[10 * MAX_TOKENS];
    int r = fread(buffer, 1, sizeof(buffer), stdin);
    if (r == 0) return 0;

    // Tokenize into an array: tokens[token_count][len] stores len followed by the token bytes
    int tokens[MAX_TOKENS][256]; 
    int token_count = 0;
    char *p = buffer;
    
    while (*p && token_count < MAX_TOKENS) {
        // Skip whitespace
        while (isspace((unsigned char)*p)) p++;
        
        if (*p == '\0' || *p == '\n' || *p == '\r') break;
        
        // Read a non-whitespace token
        char tok[MAX_STACK_SIZE];
        int len = 0;
        while (!isspace((unsigned char)*p) && *p != '\n' && *p != '\r' && len < MAX_STACK_SIZE - 1) {
            tok[len++] = *p++;
        }
        tok[len] = '\0';
        
        if (len == 0) continue;

        // Check validity of token
        int valid = 0;
        char c = tok[0];
        
        if (c == '+' || c == '-' || c == '*') {
            // Operator: must be exactly one character
            if (len == 1) {
                valid = 1;
            }
        } else if (isdigit((unsigned char)c)) {
            // Integer: must have at least one digit (already true since c is a digit)
            valid = 1;
        }

        if (!valid) {
            printf("ERROR\n");
            return 0;
        }

        // Store token
        tokens[token_count][0] = len;
        memcpy(tokens[token_count] + 1, tok, len);
        token_count++;
    }

    if (token_count == 0) {
        printf("ERROR\n");
        return 0;
    }

    // Stack
    int64 stack[MAX_STACK_SIZE];
    int top = 0;

    for (int i = 0; i < token_count; i++) {
        int len = tokens[i][0];
        char *tok_str = tokens[i] + 1;
        char c = tok_str[0];
        
        if ((c == '+' || c == '-' || c == '*') && len == 1) {
            // Operator
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[top - 1];
            int64 a = stack[top - 2];
            top -= 2;
            switch (c) {
                case '+': stack[top++] = a + b; break;
                case '-': stack[top++] = a - b; break;
                case '*': stack[top++] = a * b; break;
            }
        } else {
            // Operand: parse integer
            char *endptr;
            errno = 0;
            long long val = strtoll(tok_str, &endptr, 10);
            
            // Check if entire token was consumed
            if (endptr != tok_str + len) {
                printf("ERROR\n");
                return 0;
            }

            // Check for overflow/underflow
            if (errno == ERANGE) {
                printf("ERROR\n");
                return 0;
            }

            stack[top++] = val;
        }
    }

    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }

    return 0;
}
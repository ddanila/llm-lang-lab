#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_LEN 100
#define MAX_STACK 200

int main(void) {
    char token[MAX_TOKENS][MAX_LEN];
    int count = 0;
    
    // Read all input into a buffer first, then tokenize
    char buffer[100000] = {0};
    size_t buf_len = fread(buffer, 1, sizeof(buffer), stdin);
    
    if (buf_len == 0) {
        // Empty input - stack will be empty, which is not exactly one
        printf("ERROR\n");
        return 0;
    }
    
    // Tokenize the buffer
    char *p = buffer;
    while (*p && count < MAX_TOKENS) {
        if (!isspace((unsigned char)*p)) {
            // Start of a token
            size_t start = p - buffer;
            while (*p && !isspace((unsigned char)*p) && count < MAX_TOKENS) {
                p++;
            }
            size_t len = p - buffer - start;
            
            if (len > 0 && len < MAX_LEN) {
                memcpy(token[count], buffer + start, len);
                token[count][len] = '\0';
                count++;
            }
        } else {
            p++;
        }
    }
    
    // Debug: print tokens
    // for (int i = 0; i < count; i++) {
    //     printf("Token %d: '%s'\n", i, token[i]);
    // }
    
    // Process tokens as RPN expression
    long long stack[MAX_STACK];
    int top = 0; // Stack pointer (points to next free slot)
    
    for (int i = 0; i < count; i++) {
        char *tok = token[i];
        
        // Check if it's an operator first (must be exactly one character and is +, -, or *)
        if ((len == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*'))) {
            // Operator
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            
            long long b = stack[top - 1]; // right operand
            long long a = stack[top - 2]; // left operand
            top -= 2;
            
            if (tok[0] == '+') {
                stack[top] = a + b;
            } else if (tok[0] == '-') {
                stack[top] = a - b;
            } else if (tok[0] == '*') {
                stack[top] = a * b;
            }
        } else {
            // Must be an integer
            char *endptr;
            long long val = strtoll(tok, &endptr, 10);
            
            // Check if the entire token was consumed
            size_t tok_len = strlen(tok);
            if (endptr != tok + tok_len) {
                printf("ERROR\n");
                return 0;
            }
            
            stack[top++] = val;
        }
    }
    
    // Check final stack size
    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }
    
    return 0;
}
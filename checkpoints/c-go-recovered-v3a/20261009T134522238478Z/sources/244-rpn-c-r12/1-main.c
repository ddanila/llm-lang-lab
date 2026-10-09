#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 200
#define MAX_TOKENS 200

long stack[MAX_STACK_SIZE];
int top = -1;

int main(void) {
    char buffer[8192];
    char *tokens[MAX_TOKENS];
    int token_count = 0;
    
    // Read all input into buffer
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    // Tokenize the input
    char *ptr = buffer;
    while (*ptr && token_count < MAX_TOKENS) {
        // Skip whitespace
        while (*ptr && isspace((unsigned char)*ptr)) ptr++;
        if (!*ptr) break;
        
        // Find end of token
        char *start = ptr;
        while (*ptr && !isspace((unsigned char)*ptr)) ptr++;
        
        int len = (int)(ptr - start);
        if (len > 0) {
            tokens[token_count++] = start;
        }
    }
    
    // Process tokens as RPN
    for (int i = 0; i < token_count; i++) {
        char *tok = tokens[i];
        int len = strlen(tok);
        
        // Check if operator
        if (len == 1) {
            char op = tok[0];
            if (op == '+' || op == '-' || op == '*') {
                // Need at least 2 operands
                if (top < 1) {
                    printf("ERROR\n");
                    return 0;
                }
                
                long right = stack[top--];
                long left = stack[top--];
                
                long result;
                switch (op) {
                    case '+': result = left + right; break;
                    case '-': result = left - right; break;
                    case '*': result = left * right; break;
                }
                
                if (top >= MAX_STACK_SIZE - 1) {
                    printf("ERROR\n");
                    return 0;
                }
                stack[++top] = result;
            } else {
                // Invalid operator character
                printf("ERROR\n");
                return 0;
            }
        } else {
            // Must be an integer
            // Check for valid integer format: optional + or - followed by at least one digit
            if (len == 1) {
                // Single char that is not operator must be a digit, but we handle operators above
                printf("ERROR\n");
                return 0;
            }
            
            // Check format: starts with optional +/- then digits
            int sign = 1;
            if (tok[0] == '+') {
                if (!isdigit((unsigned char)tok[1])) {
                    printf("ERROR\n");
                    return 0;
                }
                len--; // skip +
            } else if (tok[0] == '-') {
                if (!isdigit((unsigned char)tok[1])) {
                    printf("ERROR\n");
                    return 0;
                }
                sign = -1;
                len--; // skip -
            }
            
            // Convert to long
            long val = 0;
            for (int j = 0; j < len; j++) {
                if (!isdigit((unsigned char)tok[j])) {
                    printf("ERROR\n");
                    return 0;
                }
                int digit = tok[j] - '0';
                // Check for overflow before multiplying by 10 and adding
                long max_digit = (922337203685477580L - digit) / 10;
                if ((long)(val >> 63)) { // val is signed, check high bit
                    printf("ERROR\n");
                    return 0;
                }
                val = val * 10 + digit;
            }
            
            val *= sign;
            
            if (top >= MAX_STACK_SIZE - 1) {
                printf("ERROR\n");
                return 0;
            }
            stack[++top] = val;
        }
    }
    
    // Check final stack size
    if (top != 0) {
        printf("ERROR\n");
        return 0;
    }
    
    // Print result
    printf("%ld\n", stack[0]);
    
    return 0;
}
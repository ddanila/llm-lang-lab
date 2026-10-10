#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

int main(void) {
    char token[MAX_TOKENS][128];
    int count = 0;
    
    // Read tokens until EOF or max reached
    while (count < MAX_TOKENS) {
        char c;
        if (scanf("%c", &c) != 1) break;
        
        // Skip whitespace
        if (isspace((unsigned char)c)) continue;
        
        // Check for EOF after skipping whitespace
        // Actually, scanf will return EOF, but we already checked
        // Let's read the token character by character
        
        int i = 0;
        while (i < 127) {
            if (c == EOF || !isalnum((unsigned char)c)) break;
            token[count][i++] = c;
            if (scanf("%c", &c) != 1) break;
        }
        
        // Check for invalid characters
        int j = 0;
        while (j < i) {
            unsigned char ch = (unsigned char)token[count][j];
            if (!isalnum(ch)) {
                // Invalid character found
                printf("ERROR\n");
                return 0;
            }
            j++;
        }
        
        // Skip empty tokens
        if (i == 0) continue;
        
        count++;
    }
    
    // Check for empty input
    if (count == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    // Validate each token and parse
    int64_t stack[STACK_SIZE];
    int sp = 0; // stack pointer
    
    for (int i = 0; i < count; i++) {
        char *tok = token[i];
        
        if (*tok == '+' || *tok == '-' || *tok == '*') {
            // Operator
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64_t b = stack[sp - 1];
            int64_t a = stack[sp - 2];
            sp -= 2;
            
            char op = *tok;
            if (op == '+') {
                stack[sp++] = a + b;
            } else if (op == '-') {
                stack[sp++] = a - b;
            } else if (op == '*') {
                stack[sp++] = a * b;
            }
        } else {
            // Number
            char *endptr;
            long val = strtol(tok, &endptr, 10);
            
            // Check for invalid format (must be all digits with optional sign)
            if (*tok == '+' || *tok == '-') {
                // Must have at least one digit after sign
                if (endptr == tok + 1 && !isdigit((unsigned char)*endptr)) {
                    printf("ERROR\n");
                    return 0;
                }
            } else {
                // No sign allowed for numbers
                if (*tok != '-' && *tok != '+') {
                    // This should be caught by isalnum check above
                }
            }
            
            // Check if entire token was consumed
            if (endptr != tok + i) {
                printf("ERROR\n");
                return 0;
            }
            
            stack[sp++] = val;
        }
    }
    
    // Check final stack size
    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%ld\n", stack[0]);
    
    return 0;
}
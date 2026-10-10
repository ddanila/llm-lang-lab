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
        
        int i = 0;
        while (i < 127) {
            if (c == EOF || !isalnum((unsigned char)c)) break;
            token[count][i++] = c;
            if (scanf("%c", &c) != 1) break;
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
            // Operator - must be exactly one character
            if (i != 1) {
                printf("ERROR\n");
                return 0;
            }
            
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
    
    printf("%lld\n", stack[0]);
    
    return 0;
}
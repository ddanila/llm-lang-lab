#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK 200

int main(void) {
    char token[MAX_TOKENS][100];
    int count = 0;
    
    // Read whitespace-separated tokens until EOF or max tokens reached
    while (count < MAX_TOKENS && fgets(token[count], sizeof(token[count]), stdin) != NULL) {
        // Skip leading whitespace in the line
        char *p = token[count];
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
            p++;
        }
        
        if (*p == '\0') {
            // Empty line, skip
            continue;
        }
        
        // Find end of token (whitespace or newline)
        char *end = p;
        while (*end != ' ' && *end != '\t' && *end != '\n' && *end != '\r') {
            if (*end == '\0') break;
            end++;
        }
        
        // Check for valid token (non-empty)
        if (end == p) {
            continue;
        }
        
        int len = end - p;
        if (len >= sizeof(token[count])) {
            // Token too long, truncate or error? Specification says at most 200 tokens, doesn't specify max length.
            // Assume it fits since valid integers fit in 64-bit.
            break;
        }
        
        // Copy token to our array
        memcpy(token[count], p, len);
        token[count][len] = '\0';
        count++;
    }
    
    // Process tokens as RPN expression
    long long stack[MAX_STACK];
    int top = 0; // Stack pointer (points to next free slot)
    
    for (int i = 0; i < count; i++) {
        char *tok = token[i];
        
        if (tok[0] == '+' || tok[0] == '-' || tok[0] == '*') {
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
            if (endptr != tok + strlen(tok)) {
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
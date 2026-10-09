#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

long long stack[STACK_SIZE];
int top = -1;

void push(long long val) {
    if (top >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++top] = val;
}

long long pop() {
    if (top < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int main(void) {
    char buf[1024];
    int token_count = 0;
    
    while (fgets(buf, sizeof(buf), stdin)) {
        char *p = buf;
        
        // Skip leading spaces
        while (*p && *p == ' ') p++;
        
        if (!*p) break;
        
        // Check if valid token character
        if (!isdigit((unsigned char)*p) && *p != '+' && *p != '-' && *p != '*') {
            fprintf(stderr, "ERROR\n");
            return 0;
        }
        
        // Handle sign at start of number
        if (*p == '+' || *p == '-') {
            p++;
            // Check if followed by a digit (number)
            if (!*p || !isdigit((unsigned char)*p)) {
                // Just an operator - need at least one operand
                fprintf(stderr, "ERROR\n");
                return 0;
            } else if (isdigit((unsigned char)*p)) {
                // Signed number - continue parsing
            }
        }
        
        // Parse the token
        char *endptr;
        long long val = strtoll(p, &endptr, 10);
        
        if (p == endptr) {
            // No number parsed - invalid token
            fprintf(stderr, "ERROR\n");
            return 0;
        }
        
        // Check that we consumed at least one digit and no trailing junk
        if (*endptr != '\0' && !isspace((unsigned char)*endptr)) {
            // There's more after the number - invalid character
            fprintf(stderr, "ERROR\n");
            return 0;
        }
        
        push(val);
    }
    
    if (top != 0) {
        fprintf(stderr, "ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

static long long stack[STACK_SIZE];
static int top = -1;

static void push(long long val) {
    if (top >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++top] = val;
}

int main(void) {
    char buf[256];
    if (!fgets(buf, sizeof(buf), stdin)) {
        // No input at all -> empty stack -> ERROR
        printf("ERROR\n");
        return 0;
    }

    char *p = buf;
    int token_count = 0;
    
    while (1) {
        // Skip leading whitespace
        while (*p && isspace((unsigned char)*p)) p++;
        
        if (*p == '\0' || *p == '\n') break;

        // Determine length of token
        const char *token_start = p;
        while (*p && !isspace((unsigned char)*p)) {
            p++;
        }
        int len = (int)(p - token_start);
        
        if (len == 0) continue;

        // Check for operator first: single character +, -, or *
        char first = token_start[0];
        
        if (len == 1 && (first == '+' || first == '-' || first == '*')) {
            // Operator: pop 2 operands, compute, push result
            if (top < 1) {
                printf("ERROR\n");
                return 0;
            }
            long long right = stack[top--];
            long long left = stack[top--];
            long long result;
            if (first == '+') {
                result = left + right;
            } else if (first == '-') {
                result = left - right;
            } else if (first == '*') {
                result = left * right;
            }
            push(result);
        } else {
            // Must be an integer
            // Check for valid integer format: optional leading +/- and at least one digit
            int has_sign = (token_start[0] == '+' || token_start[0] == '-');
            
            // Check all characters are valid (digit or sign only)
            for (int i = 0; i < len; i++) {
                if (!isdigit((unsigned char)token_start[i]) && 
                    !(i == 0 && (token_start[i] == '+' || token_start[i] == '-'))) {
                    printf("ERROR\n");
                    return 0;
                }
            }
            
            // Must have at least one digit
            int has_digit = 0;
            for (int i = 0; i < len; i++) {
                if (isdigit((unsigned char)token_start[i])) {
                    has_digit = 1;
                    break;
                }
            }
            
            if (!has_digit) {
                printf("ERROR\n");
                return 0;
            }
            
            // Parse the integer
            char *endptr;
            long long val = strtoll(token_start, &endptr, 10);
            if (endptr != token_start + len) {
                printf("ERROR\n");
                return 0;
            }
            push(val);
        }
        
        token_count++;
        if (token_count >= MAX_TOKENS) break;
    }

    // Check stack size - must be exactly 1
    if (top != 0) {
        printf("ERROR\n");
        return 0;
    }

    printf("%lld\n", stack[top]);

    return 0;
}
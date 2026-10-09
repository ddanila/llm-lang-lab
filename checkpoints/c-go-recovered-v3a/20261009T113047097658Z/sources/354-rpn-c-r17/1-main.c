#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

int peek() {
    if (top < 0) return 0;
    return stack[top];
}

int main(void) {
    char buf[MAX_TOKENS * 20]; // generous buffer
    int written = 0;
    
    while (fgets(buf, sizeof(buf), stdin)) {
        for (char *p = buf; p && *p == ' '; p++) {}
        if (!*p) break;
        
        char *token_start = p;
        char c = *p;
        
        // Check if it's a number or operator
        int is_number = 0;
        
        // Handle optional sign for numbers only (operators don't have signs in this spec)
        if (c == '+' || c == '-') {
            // Could be an operator or start of a number
            p++;
            if (*p == '\0' || !isdigit(*p)) {
                // It's just an operator with no operand following immediately
                // But we need to check context
                is_number = 0;
            } else if (isdigit(*p)) {
                // It's a signed number
                is_number = 1;
            } else {
                // Just a sign character by itself - invalid
                fprintf(stderr, "Invalid token\n");
                return 0;
            }
        } else if (isdigit(c)) {
            is_number = 1;
        } else if (c == '+' || c == '-' || c == '*') {
            // Operator without sign check needed here since we already handled signs above
            is_number = 0;
        } else {
            // Invalid character
            fprintf(stderr, "Invalid token\n");
            return 0;
        }
        
        if (is_number) {
            // Parse the number including optional sign
            char *endptr;
            long long val = strtoll(token_start, &endptr, 10);
            
            // Check for parsing errors or overflow
            if (endptr == token_start || *endptr != '\0' && !isspace(*endptr)) {
                fprintf(stderr, "Invalid number\n");
                return 0;
            }
            
            push(val);
        } else {
            // It's an operator: +, -, *
            char op = c;
            
            if (top < 1) {
                fprintf(stderr, "ERROR\n");
                return 0;
            }
            
            long long b = pop();
            long long a = pop();
            long long result;
            
            switch (op) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                default:
                    fprintf(stderr, "Invalid operator\n");
                    return 0;
            }
            
            // Check for overflow (simplified check)
            if (op == '+' && (a > 0 && b > LLONG_MAX - a || a < 0 && b < LLONG_MIN - a)) {
                fprintf(stderr, "ERROR\n");
                return 0;
            }
            if (op == '-' && (a > LLONG_MAX + b || a < LLONG_MIN - b)) {
                fprintf(stderr, "ERROR\n");
                return 0;
            }
            if (op == '*' && (a != 0 && b != 0 && (a > 0) ^ (b > 0) && 
                           (LLONG_MAX / a < b || LLONG_MIN / a > b))) {
                fprintf(stderr, "ERROR\n");
                return 0;
            }
            
            push(result);
        }
        
        // Consume the rest of the line/tokens
        while (*p && !isspace(*p)) p++;
        while (*p && isspace(*p)) p++;
    }
    
    if (top != 0) {
        fprintf(stderr, "ERROR\n");
        return 0;
    }
    
    // Print the result
    printf("%lld\n", stack[0]);
    
    return 0;
}
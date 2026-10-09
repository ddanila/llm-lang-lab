#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 10000

typedef struct {
    long long stack[MAX_STACK_SIZE];
    int top;
} Stack;

void init_stack(Stack *s) {
    s->top = 0;
}

int push(Stack *s, long long val) {
    if (s->top >= MAX_STACK_SIZE) return -1;
    s->stack[s->top++] = val;
    return 0;
}

long long pop(Stack *s) {
    if (s->top == 0) return 0;
    return s->stack[--s->top];
}

bool is_valid_token(const char *token, char *num_out, int *num_len) {
    // Check for empty token
    if (*token == '\0') return false;
    
    // Token must start with optional + or - followed by at least one digit
    const char *p = token;
    if (*p == '+' || *p == '-') {
        p++;
    }
    
    // Must have at least one digit
    if (*p == '\0') return false;
    
    // Check that remaining characters are digits
    while (*p) {
        if (!isdigit((unsigned char)*p)) return false;
        p++;
    }
    
    // Convert to number
    *num_len = 0;
    long long val = 0;
    const char *start = token;
    
    if (token[0] == '+' || token[0] == '-') {
        sign = (token[0] == '-') ? -1 : 1;
        p++;
    } else {
        sign = 1;
    }
    
    while (*p) {
        val = val * 10 + (*p - '0');
        if (*num_len > 0 && (val < -922337203685477580LL || val > 922337203685477580LL)) {
            // Overflow check would be here but problem says all fit in 64-bit
        }
        p++;
    }
    
    return true;
}

int main() {
    Stack stack;
    init_stack(&stack);
    
    char token[256];
    while (scanf("%255s", token) == 1) {
        int len;
        if (!is_valid_token(token, &len)) {
            printf("ERROR\n");
            return 0;
        }
        
        long long val = strtoll(token, NULL, 10);
        
        // Check if operator
        if (strcmp(token, "+") == 0) {
            if (stack.top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = pop(&stack);
            long long a = pop(&stack);
            push(&stack, a + b);
        } else if (strcmp(token, "-") == 0) {
            if (stack.top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = pop(&stack);
            long long a = pop(&stack);
            push(&stack, a - b);
        } else if (strcmp(token, "*") == 0) {
            if (stack.top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = pop(&stack);
            long long a = pop(&stack);
            push(&stack, a * b);
        } else {
            // It's a number (already validated)
            push(&stack, val);
        }
    }
    
    if (stack.top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack.stack[0]);
    }
    
    return 0;
}
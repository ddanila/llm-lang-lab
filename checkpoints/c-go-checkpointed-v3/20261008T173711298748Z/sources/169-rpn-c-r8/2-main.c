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

int main() {
    Stack stack;
    init_stack(&stack);
    
    char token[256];
    while (scanf("%255s", token) == 1) {
        int len = 0;
        
        // Check if operator
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0) {
            // It's an operator
            if (stack.top < 2) {
                printf("ERROR\n");
                return 0;
            }
            
            if (strcmp(token, "+") == 0) {
                long long b = pop(&stack);
                long long a = pop(&stack);
                push(&stack, a + b);
            } else if (strcmp(token, "-") == 0) {
                long long b = pop(&stack);
                long long a = pop(&stack);
                push(&stack, a - b);
            } else if (strcmp(token, "*") == 0) {
                long long b = pop(&stack);
                long long a = pop(&stack);
                push(&stack, a * b);
            }
        } else {
            // It's a number - validate it has proper format
            if (token[0] != '+' && token[0] != '-') {
                // No sign, must be all digits
                for (int i = 0; token[i] != '\0'; i++) {
                    if (!isdigit((unsigned char)token[i])) {
                        printf("ERROR\n");
                        return 0;
                    }
                }
            } else {
                // Has sign, rest must be digits
                const char *p = token + 1;
                if (*p == '\0') {
                    printf("ERROR\n");
                    return 0;
                }
                for (; *p != '\0'; p++) {
                    if (!isdigit((unsigned char)*p)) {
                        printf("ERROR\n");
                        return 0;
                    }
                }
            }
            
            long long val = strtoll(token, NULL, 10);
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
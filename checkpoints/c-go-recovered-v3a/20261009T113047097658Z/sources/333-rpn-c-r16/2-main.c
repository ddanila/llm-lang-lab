#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 1000

typedef struct {
    long long *stack;
    int top;
} Stack;

void init_stack(Stack *s) {
    s->stack = malloc(STACK_SIZE * sizeof(long long));
    s->top = 0;
}

int push(Stack *s, long long val) {
    if (s->top >= STACK_SIZE) return 0;
    s->stack[s->top++] = val;
    return 1;
}

long long pop(Stack *s) {
    if (s->top == 0) return 0;
    return s->stack[--s->top];
}

int is_valid_number(const char *str) {
    if (str[0] == '\0') return 0;
    int has_digit = 0;
    for (const char *p = str; *p != '\0'; p++) {
        if (!isdigit((unsigned char)*p) && *p != '+' && *p != '-') {
            return 0;
        }
        if (*p == '+' || *p == '-') {
            if (has_digit) return 0;
        } else {
            has_digit = 1;
        }
    }
    return has_digit;
}

long long parse_number(const char *str) {
    char buf[64];
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        buf[i] = str[i];
    }
    buf[len] = '\0';
    return atoll(buf);
}

int main(void) {
    char buffer[10240];
    size_t n = fread(buffer, 1, sizeof(buffer), stdin);
    
    Stack s;
    init_stack(&s);
    
    int pos = 0;
    while (pos < n) {
        // Skip whitespace
        while (pos < n && isspace((unsigned char)buffer[pos])) {
            pos++;
        }
        if (pos >= n) break;
        
        // Find end of token
        int end = pos;
        while (end < n && !isspace((unsigned char)buffer[end])) {
            end++;
        }
        
        const char *token = &buffer[pos];
        int len = end - pos;
        
        if (len == 0) continue;
        
        if (token[0] == '+' || token[0] == '-' || token[0] == '*') {
            long long b = pop(&s);
            long long a = pop(&s);
            if (s.top < 2) {
                printf("ERROR\n");
                return 0;
            }
            switch (token[0]) {
                case '+': push(&s, a + b); break;
                case '-': push(&s, a - b); break;
                case '*': push(&s, a * b); break;
            }
        } else if (is_valid_number(token)) {
            long long val = parse_number(token);
            push(&s, val);
        } else {
            printf("ERROR\n");
            return 0;
        }
        
        pos = end;
    }
    
    if (s.top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", s.stack[0]);
    }
    
    free(s.stack);
    return 0;
}
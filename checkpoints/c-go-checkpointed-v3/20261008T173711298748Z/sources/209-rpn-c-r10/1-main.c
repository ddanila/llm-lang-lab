#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 1000

typedef struct {
    long long values[MAX_STACK_SIZE];
    int size;
} Stack;

void stack_init(Stack *s) {
    s->size = 0;
}

int stack_empty(const Stack *s) {
    return s->size == 0;
}

long long stack_pop(Stack *s) {
    if (stack_empty(s)) {
        return 0;
    }
    return s->values[--s->size];
}

void stack_push(Stack *s, long long value) {
    if (s->size < MAX_STACK_SIZE) {
        s->values[s->size++] = value;
    }
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

long long parse_number(const char *str, int len) {
    long long result = 0;
    int sign = 1;
    
    if (len == 0) {
        return 0; // Should not happen with valid input
    }
    
    // Check for optional leading + or -
    if (str[0] == '+') {
        result = parse_number(str + 1, len - 1);
    } else if (str[0] == '-') {
        sign = -1;
        result = parse_number(str + 1, len - 1);
    } else if (!is_digit(str[0])) {
        return 0; // Invalid character
    }
    
    for (int i = 0; i < len; i++) {
        if (!is_digit(str[i])) {
            return 0; // Invalid character in number
        }
        result = result * 10 + (str[i] - '0');
    }
    
    return result * sign;
}

int is_valid_number(const char *token) {
    int len = strlen(token);
    
    if (len == 0) {
        return 0;
    }
    
    // Check for optional leading + or -
    int i = 0;
    if (token[0] == '+') {
        i = 1;
    } else if (token[0] == '-') {
        i = 1;
    }
    
    // Must have at least one digit after optional sign
    if (i >= len) {
        return 0;
    }
    
    for (; i < len; i++) {
        if (!is_digit(token[i])) {
            return 0;
        }
    }
    
    return 1;
}

int is_operator(const char *token) {
    return (strcmp(token, "+") == 0) || 
           (strcmp(token, "-") == 0) || 
           (strcmp(token, "*") == 0);
}

int main() {
    Stack stack;
    stack_init(&stack);
    
    char buffer[1024];
    char *token = NULL;
    int token_count = 0;
    
    // Read all input into a buffer
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    // Tokenize the input
    token = strtok(buffer, " \t\n\r");
    while (token != NULL && token_count < MAX_TOKENS) {
        if (is_operator(token)) {
            if (stack.size < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long right = stack_pop(&stack);
            long long left = stack_pop(&stack);
            
            switch (*token) {
                case '+':
                    stack_push(&stack, left + right);
                    break;
                case '-':
                    stack_push(&stack, left - right);
                    break;
                case '*':
                    stack_push(&stack, left * right);
                    break;
            }
        } else if (is_valid_number(token)) {
            long long value = parse_number(token, strlen(token));
            stack_push(&stack, value);
        } else {
            printf("ERROR\n");
            return 0;
        }
        
        token_count++;
        token = strtok(NULL, " \t\n\r");
    }
    
    if (stack.size != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack.values[0]);
    }
    
    return 0;
}
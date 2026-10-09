#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 1000

typedef long long ll;

ll stack[STACK_SIZE];
int sp = -1;

void push(ll v) {
    if (sp >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++sp] = v;
}

ll pop(void) {
    if (sp < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return stack[sp--];
}

int main(void) {
    char buffer[MAX_TOKENS + 1];
    int n = 0;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0; // empty input -> ERROR per spec
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    char *token = strtok(buffer, " \t\n\r");
    while (token != NULL) {
        if (n >= MAX_TOKENS) {
            fprintf(stderr, "Too many tokens\n");
            return 0;
        }
        
        size_t tlen = strlen(token);
        if (tlen == 0) continue;
        
        // Check for valid integer: optional + or -, then at least one digit
        if (token[0] == '+' || token[0] == '-') {
            if (tlen < 2) {
                fprintf(stderr, "Invalid token: %s\n", token);
                return 0;
            }
            if (!isdigit((unsigned char)token[1])) {
                fprintf(stderr, "Invalid token: %s\n", token);
                return 0;
            }
        } else if (token[0] == '-' && tlen > 1 && !isdigit((unsigned char)token[1])) {
            // Leading - followed by non-digit is invalid (like "-+3" or "--")
            fprintf(stderr, "Invalid token: %s\n", token);
            return 0;
        } else if (!isdigit((unsigned char)token[0]) && token[0] != '+' && token[0] != '-') {
            // Not a valid integer and not an operator
            fprintf(stderr, "Invalid token: %s\n", token);
            return 0;
        }
        
        // Check for operators
        if (strcmp(token, "+") == 0) {
            push(pop());
            push(pop());
            n++;
        } else if (strcmp(token, "-") == 0) {
            ll right = pop();
            ll left = pop();
            push(left - right);
            n++;
        } else if (strcmp(token, "*") == 0) {
            ll right = pop();
            ll left = pop();
            push(left * right);
            n++;
        } else {
            // Parse as integer
            char *endptr;
            ll val = strtoll(token, &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "Invalid token: %s\n", token);
                return 0;
            }
            push(val);
            n++;
        }
        
        token = strtok(NULL, " \t\n\r");
    }
    
    if (sp != 0) {
        fprintf(stderr, "Final stack size not exactly one\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    
    return 0;
}
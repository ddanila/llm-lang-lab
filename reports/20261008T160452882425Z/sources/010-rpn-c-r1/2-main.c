#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

long long stack[MAX_STACK_SIZE];
int top = -1;

void push(long long val) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++top] = val;
}

long long pop(void) {
    if (top < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*';
}

long long parse_number(const char *token) {
    char *endptr;
    return strtoll(token, &endptr, 10);
}

int main(void) {
    char buffer[65536];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    if (len == 0) {
        printf("ERROR\n");
        return 0;
    }

    char *tokens[MAX_TOKENS];
    int token_count = 0;
    const char *p = buffer;
    while (*p && token_count < MAX_TOKENS) {
        if (is_operator(*p)) {
            tokens[token_count++] = (char *)p;
            p++;
        } else if (isdigit((unsigned char)*p) || *p == '+' || *p == '-') {
            const char *start = p;
            while (*p && (*p == '0' || isdigit((unsigned char)*p))) p++;
            tokens[token_count++] = (char *)start;
        } else if (*p != ' ' && *p != '\n' && *p != '\t') {
            // Invalid character, but skip it and continue
            while (*p && (*p == ' ' || *p == '\n' || *p == '\t')) p++;
        } else {
            p++;
        }
    }

    if (token_count == 0) {
        printf("ERROR\n");
        return 0;
    }

    for (int i = 0; i < token_count; i++) {
        const char *tok = tokens[i];
        int len_tok = strlen(tok);

        if (len_tok == 1 && is_operator(tok[0])) {
            if (top < 1) {
                printf("ERROR\n");
                return 0;
            }
            long long right = pop();
            long long left = pop();
            char op = tok[0];
            long long result;
            switch (op) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                default: printf("ERROR\n"); return 0;
            }
            push(result);
        } else if (len_tok > 1 || !is_operator(tok[0])) {
            // Try to parse as integer - manual parsing to avoid errno issues
            char *endptr;
            long long val = strtoll(tok, &endptr, 10);
            // Check if entire token was consumed and no error occurred
            int consumed = (endptr == tok + len_tok);
            if (!consumed) {
                printf("ERROR\n");
                return 0;
            }
            push(val);
        } else {
            printf("ERROR\n");
            return 0;
        }
    }

    if (top != 0) {
        printf("ERROR\n");
    } else {
        // Check if stack is empty
        if (top == -1) {
            printf("ERROR\n");
        } else {
            printf("%lld\n", stack[top]);
        }
    }

    return 0;
}
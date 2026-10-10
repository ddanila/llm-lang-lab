#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 10000

long long stack[STACK_SIZE];
int top = 0;

void push(long long val) {
    if (top >= STACK_SIZE) {
        printf("ERROR\n");
        exit(0);
    }
    stack[top++] = val;
}

long long pop(void) {
    if (top < 1) return 0;
    long long res = stack[--top];
    if (top < 1) return 0;
    return stack[top - 1];
}

int peek(int idx) {
    if (idx >= top) return 0;
    return stack[idx];
}

int main(void) {
    char buffer[4096];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("ERROR\n");
        return 0;
    }

    int n_tokens = 0;
    char *token = strtok(buffer, " \t\n\r");
    while (token != NULL && n_tokens < MAX_TOKENS) {
        if (*token == '+' || *token == '-' || *token == '*') {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[--top];
            long long a = stack[--top];
            push(a);
            switch (*token) {
                case '+': push(a + b); break;
                case '-': push(a - b); break;
                case '*': push(a * b); break;
            }
        } else {
            char *endptr;
            long long val = strtoll(token, &endptr, 10);
            if (endptr == token || (*endptr != '\0' && !isspace((unsigned char)*endptr))) {
                printf("ERROR\n");
                return 0;
            }
            push(val);
        }
        n_tokens++;
        token = strtok(NULL, " \t\n\r");
    }

    if (n_tokens == 0 || top != 1) {
        printf("ERROR\n");
        return 0;
    }

    printf("%lld\n", stack[0]);
    return 0;
}
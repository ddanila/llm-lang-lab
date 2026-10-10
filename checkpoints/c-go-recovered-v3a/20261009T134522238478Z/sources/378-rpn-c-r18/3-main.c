#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

typedef long long int64;

int main(void) {
    char buffer[10000];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("ERROR\n");
        return 0;
    }

    int64 stack[MAX_STACK_SIZE];
    int token_count = 0;
    char *start = buffer;
    while (*start && token_count < MAX_TOKENS) {
        // Skip whitespace
        while (*start && isspace((unsigned char)*start)) start++;
        if (!*start) break;

        // Find end of token
        char *end = start + 1;
        while (*end && !isspace((unsigned char)*end) && token_count < MAX_TOKENS) {
            end++;
        }
        int len = end - start;
        if (len == 0) break;

        // Check for operators first
        if (len == 1) {
            if (start[0] == '+' || start[0] == '-' || start[0] == '*') {
                char op = start[0];
                if (token_count < 2) {
                    printf("ERROR\n");
                    return 0;
                }
                int64 b = stack[--token_count];
                int64 a = stack[--token_count];
                int64 res;
                if (op == '+') res = a + b;
                else if (op == '-') res = a - b;
                else if (op == '*') res = a * b;
                else {
                    printf("ERROR\n");
                    return 0;
                }
                if (token_count < MAX_STACK_SIZE) {
                    stack[token_count++] = res;
                }
            } else {
                // Single non-operator char is invalid
                printf("ERROR\n");
                return 0;
            }
        } else {
            // Multi-char token: must be an integer
            if (start[0] == '+' && isdigit((unsigned char)start[1])) {
                long long val = strtoll(start, &end, 10);
                if (token_count < MAX_STACK_SIZE) {
                    stack[token_count++] = val;
                }
            } else if (start[0] == '-' && isdigit((unsigned char)start[1])) {
                long long val = strtoll(start, &end, 10);
                if (token_count < MAX_STACK_SIZE) {
                    stack[token_count++] = val;
                }
            } else {
                // Invalid token format
                printf("ERROR\n");
                return 0;
            }
        }
    }

    if (token_count != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }

    return 0;
}
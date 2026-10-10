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

        // Validate and parse token
        if (len > 1 && start[0] == '+' && isdigit((unsigned char)start[1])) {
            // Leading + followed by digit
            long long val = strtoll(start, &end, 10);
            if (token_count < MAX_STACK_SIZE) {
                stack[token_count++] = val;
            }
        } else if (len == 1 && start[0] == '-') {
            // Single minus? Not valid integer, but could be unary minus in some contexts.
            // However, spec says "signed decimal integers or operators". 
            // A single '-' is not a valid integer token per spec ("at least one digit").
            // It's also not an operator (+, -, *). So it's invalid.
            printf("ERROR\n");
            return 0;
        } else if (len > 1 && start[0] == '-' && isdigit((unsigned char)start[1])) {
            // Negative number
            long long val = strtoll(start, &end, 10);
            if (token_count < MAX_STACK_SIZE) {
                stack[token_count++] = val;
            }
        } else {
            // Check for operator
            if (len == 1 && (start[0] == '+' || start[0] == '-' || start[0] == '*')) {
                // Single char operator
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
                // Invalid token
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
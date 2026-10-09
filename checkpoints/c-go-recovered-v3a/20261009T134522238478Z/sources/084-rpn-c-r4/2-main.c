#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

int main(void) {
    char buffer[1024 * 8];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("ERROR\n");
        return 0;
    }

    size_t len = strlen(buffer);
    if (len == 0) {
        printf("ERROR\n");
        return 0;
    }

    // Remove trailing newline/carriage return
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[--len] = '\0';
    }

    int stack[MAX_STACK_SIZE];
    int top = 0; // points to next free slot, so stack[0..top-1] are valid

    char *token = strtok(buffer, " \t\n\r");
    while (token != NULL) {
        size_t tlen = strlen(token);
        if (tlen == 0) {
            token = strtok(NULL, " \t\n\r");
            continue;
        }

        // Check if it's an operator
        int is_op = 0;
        if (tlen == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*')) {
            is_op = 1;
        } else {
            // Must be a valid integer: optional + or - followed by at least one digit
            if (!isdigit((unsigned char)token[0]) && token[0] != '+' && token[0] != '-') {
                printf("ERROR\n");
                return 0;
            }
            if ((token[0] == '+' || token[0] == '-') && tlen == 1) {
                // Sign alone is invalid (need at least one digit)
                printf("ERROR\n");
                return 0;
            }
            if (token[0] == '-' && tlen > 1 && !isdigit((unsigned char)token[1])) {
                // Multiple signs like -- or -+ not allowed, but handled by isdigit check
            }
            if (token[0] == '+' || token[0] == '-') {
                for (size_t i = 1; i < tlen; ++i) {
                    if (!isdigit((unsigned char)token[i])) {
                        printf("ERROR\n");
                        return 0;
                    }
                }
            } else {
                for (size_t i = 0; i < tlen; ++i) {
                    if (!isdigit((unsigned char)token[i])) {
                        printf("ERROR\n");
                        return 0;
                    }
                }
            }
        }

        if (is_op) {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            int right = stack[top - 1];
            int left = stack[top - 2];
            top -= 2;
            switch (token[0]) {
                case '+':
                    stack[top++] = left + right;
                    break;
                case '-':
                    stack[top++] = left - right;
                    break;
                case '*':
                    // Check for overflow before multiplying
                    if (right != 0 && (left > LONG_MAX / right || left < LONG_MIN / right)) {
                        printf("ERROR\n");
                        return 0;
                    }
                    stack[top++] = left * right;
                    break;
            }
        } else {
            // Parse integer
            long long val = 0;
            int negative = 0;
            size_t i = 0;
            if (token[i] == '+' || token[i] == '-') {
                if (token[i] == '-') negative = 1;
                i++;
            }
            // Now parse digits
            for (; i < tlen; ++i) {
                val = val * 10 + (token[i] - '0');
            }
            if (negative) val = -val;
            
            // Check overflow/underflow
            if (val > LONG_MAX || val < LONG_MIN) {
                printf("ERROR\n");
                return 0;
            }

            stack[top++] = (int)val;
        }

        token = strtok(NULL, " \t\n\r");
    }

    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%d\n", stack[0]);
    }

    return 0;
}
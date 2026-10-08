#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

int main(void) {
    char buf[65536];
    if (!fgets(buf, sizeof(buf), stdin)) {
        return 0;
    }

    size_t len = strlen(buf);
    int tokens[MAX_TOKENS];
    int token_count = 0;
    int stack[MAX_STACK_SIZE];
    int sp = -1;

    for (size_t i = 0; i < len && token_count < MAX_TOKENS; ) {
        // Skip whitespace
        while (i < len && isspace((unsigned char)buf[i])) i++;
        if (i >= len) break;

        int is_op = 0;
        size_t start = i;

        if (buf[i] == '+' || buf[i] == '-' || buf[i] == '*') {
            // Check if it's a unary minus at the start of a number or operator
            if (buf[i] == '-') {
                // Could be unary minus for a number or an operator '-'
                // Peek ahead to see if there are more digits
                size_t j = i + 1;
                while (j < len && isspace((unsigned char)buf[j])) j++;
                if (j < len && buf[j] >= '0' && buf[j] <= '9') {
                    // It's a unary minus for a number
                    is_op = 0;
                } else if (j < len && (buf[j] == '+' || buf[j] == '-' || buf[j] == '*')) {
                    // Multiple operators in a row - this is an operator
                    is_op = 1;
                } else {
                    // No digit following, treat as invalid token
                    printf("ERROR\n");
                    return 0;
                }
            } else if (buf[i] == '+' || buf[i] == '*') {
                is_op = 1;
            }

            if (is_op) {
                tokens[token_count++] = buf[i]; // store operator as char value
                i++;
                continue;
            }
        }

        // Read the number
        size_t j = i;
        while (j < len && !isspace((unsigned char)buf[j])) j++;
        if (j == i) {
            // No characters read, invalid token
            printf("ERROR\n");
            return 0;
        }

        // Parse the number
        int64_t num = 0;
        int neg = 0;
        size_t k = i;

        if (buf[k] == '+') {
            k++;
        } else if (buf[k] == '-') {
            neg = 1;
            k++;
        }

        if (k >= j || !isdigit((unsigned char)buf[k])) {
            // No digits, invalid token
            printf("ERROR\n");
            return 0;
        }

        while (k < j && isdigit((unsigned char)buf[k])) {
            num = num * 10 + (buf[k] - '0');
            k++;
        }

        if (neg) num = -num;
        tokens[token_count++] = (int)num;

        i = j;
    }

    // Evaluate RPN
    for (int t = 0; t < token_count; t++) {
        int val = tokens[t];

        if (val == '+') {
            if (sp < 1) {
                printf("ERROR\n");
                return 0;
            }
            int b = stack[sp--];
            int a = stack[sp--];
            stack[++sp] = a + b;
        } else if (val == '-') {
            if (sp < 1) {
                printf("ERROR\n");
                return 0;
            }
            int b = stack[sp--];
            int a = stack[sp--];
            stack[++sp] = a - b;
        } else if (val == '*') {
            if (sp < 1) {
                printf("ERROR\n");
                return 0;
            }
            int b = stack[sp--];
            int a = stack[sp--];
            stack[++sp] = a * b;
        } else {
            // Number token
            if (sp >= MAX_STACK_SIZE - 1) {
                printf("ERROR\n");
                return 0;
            }
            stack[++sp] = val;
        }
    }

    if (sp != 0) {
        printf("ERROR\n");
        return 0;
    }

    printf("%d\n", stack[0]);

    return 0;
}
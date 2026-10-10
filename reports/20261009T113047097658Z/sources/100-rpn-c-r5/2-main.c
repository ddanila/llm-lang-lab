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

        // Read until next whitespace or end
        size_t j = i;
        while (j < len && !isspace((unsigned char)buf[j])) j++;

        // Check if this is an operator token (standalone +, -, *)
        // Operators are only valid when they are the entire token
        int is_operator = 0;
        size_t tok_len = j - i;
        
        if (tok_len == 1) {
            char c = buf[i];
            if (c == '+' || c == '-' || c == '*') {
                is_operator = 1;
            }
        }

        if (is_operator) {
            // Check stack before pushing operator
            if (sp < 0) {
                printf("ERROR\n");
                return 0;
            }
            int op_code = buf[i];
            if (op_code == '+') {
                if (sp < 1) {
                    printf("ERROR\n");
                    return 0;
                }
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a + b;
            } else if (op_code == '-') {
                if (sp < 1) {
                    printf("ERROR\n");
                    return 0;
                }
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a - b;
            } else if (op_code == '*') {
                if (sp < 1) {
                    printf("ERROR\n");
                    return 0;
                }
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a * b;
            }
            i = j;
            continue;
        }

        // Parse number (must have at least one digit)
        size_t k = i;
        
        // Check for optional leading + or -
        if (buf[k] == '+') {
            k++;
        } else if (buf[k] == '-') {
            k++;
        }

        // Must have at least one digit
        if (k >= j || !isdigit((unsigned char)buf[k])) {
            printf("ERROR\n");
            return 0;
        }

        int64_t num = 0;
        int neg = (buf[i] == '-');
        
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
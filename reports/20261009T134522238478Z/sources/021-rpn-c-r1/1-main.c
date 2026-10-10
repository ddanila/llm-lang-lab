#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

typedef long long int64;

int main(void) {
    char buffer[10 * MAX_TOKENS];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("ERROR\n");
        return 0;
    }

    size_t len = strlen(buffer);
    int64 stack[STACK_SIZE];
    int top = 0; // points to next free slot

    char *p = buffer;
    while (p < buffer + len) {
        // Skip whitespace
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') p++;
        if (p >= buffer + len) break;

        int is_op = 0;
        char op_char = 0;

        if (*p == '+') {
            op_char = '+';
            is_op = 1;
            p++;
        } else if (*p == '-') {
            // Check if it's a unary minus at start of token or after whitespace
            // But in RPN, - is an operator. However, - can also be part of a negative number.
            // We need to distinguish.
            // A token starting with '-' followed by digits is a negative number.
            // A standalone '-' is an operator.
            if (isdigit(*(p + 1))) {
                // It's part of a negative number
                op_char = 0;
                p++;
            } else {
                op_char = '-';
                is_op = 1;
                p++;
            }
        } else if (*p == '*') {
            op_char = '*';
            is_op = 1;
            p++;
        } else if (isdigit(*p) || *p == '+') {
            // It's a number
            if (*p == '+') {
                p++;
            }
            char *num_end = p;
            while (isdigit(*p)) p++;
            char *endptr = NULL;
            long long val = strtoll(num_end, &endptr, 10);
            // Check if conversion was successful and no extra characters
            if (endptr != p) {
                printf("ERROR\n");
                return 0;
            }
            stack[top++] = val;
        } else {
            // Invalid character
            printf("ERROR\n");
            return 0;
        }

        if (is_op) {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[top - 1]; // right operand
            int64 a = stack[top - 2]; // left operand
            top -= 2;
            switch (op_char) {
                case '+':
                    stack[top++] = a + b;
                    break;
                case '-':
                    stack[top++] = a - b;
                    break;
                case '*':
                    stack[top++] = a * b;
                    break;
            }
        }
    }

    if (top != 1) {
        printf("ERROR\n");
        return 0;
    }

    printf("%lld\n", stack[0]);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

int main(void) {
    char buffer[MAX_TOKENS * 15 + 1];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("ERROR\n");
        return 0;
    }

    int n = 0;
    for (int i = 0; i < (int)strlen(buffer); ) {
        // Skip whitespace
        while (i < (int)strlen(buffer) && isspace((unsigned char)buffer[i])) {
            i++;
        }
        if (i >= (int)strlen(buffer)) break;

        // Parse token
        char *start = buffer + i;
        char c = start[0];

        // Check for operator first
        if (c == '+' || c == '-' || c == '*') {
            n++;
            i++;
            continue;
        }

        // Must be a digit or leading +/- followed by digits
        if (!isdigit((unsigned char)c)) {
            printf("ERROR\n");
            return 0;
        }

        // Read number - use endptr to advance past the number
        char *endptr = NULL;
        long val = strtol(start, &endptr, 10);
        if (start == endptr) {
            printf("ERROR\n");
            return 0;
        }

        n++;
        i += (int)(endptr - start);
    }

    // Process tokens again to evaluate RPN
    int token_idx = 0;
    long stack[MAX_STACK_SIZE];
    int top = 0;

    while (token_idx < n) {
        char *start = buffer + i;
        char c = start[0];

        if (c == '+' || c == '-' || c == '*') {
            // Operator
            long left, right;
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            right = stack[top - 1];
            left = stack[top - 2];
            top--;
            switch (c) {
                case '+': stack[top++] = left + right; break;
                case '-': stack[top++] = left - right; break;
                case '*': stack[top++] = left * right; break;
            }
            // Advance i past the operator
            char *op_end = start + 1;
            while (op_end < buffer + strlen(buffer) && !isspace((unsigned char)*op_end)) {
                op_end++;
            }
            i = (int)(op_end - buffer);
            token_idx++;
        } else if (isdigit((unsigned char)c)) {
            // Number
            char *endptr2 = NULL;
            long val2 = strtol(start, &endptr2, 10);
            if (start == endptr2) {
                printf("ERROR\n");
                return 0;
            }
            stack[top++] = val2;
            // Advance i past the number
            char *num_end = endptr2;
            while (num_end < buffer + strlen(buffer) && !isspace((unsigned char)*num_end)) {
                num_end++;
            }
            i = (int)(num_end - buffer);
            token_idx++;
        } else {
            printf("ERROR\n");
            return 0;
        }
    }

    if (top != 1) {
        printf("ERROR\n");
        return 0;
    }

    printf("%ld\n", stack[0]);
    return 0;
}
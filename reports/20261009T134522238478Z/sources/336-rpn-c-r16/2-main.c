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

        // Read number
        char *endptr = NULL;
        long val = strtol(start, &endptr, 10);
        if (start == endptr) {
            printf("ERROR\n");
            return 0;
        }

        n++;
        i += (endptr - start);
    }

    // Stack
    long stack[MAX_STACK_SIZE];
    int top = 0;

    for (int j = 0; j < n; j++) {
        while (j < n) {
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
                j++; // consume operator
                i += strlen(start); // skip past operator (already advanced by loop)
                break;
            } else {
                // Number
                char *endptr2 = NULL;
                long val2 = strtol(start, &endptr2, 10);
                if (start == endptr2) {
                    printf("ERROR\n");
                    return 0;
                }
                stack[top++] = val2;
                j++;
                i += (endptr2 - start);
                break;
            }
        }
    }

    // Wait, the above logic is flawed because I'm re-parsing. Let me rewrite properly.
    return 0;
}
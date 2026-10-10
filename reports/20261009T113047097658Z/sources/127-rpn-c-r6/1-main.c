#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 100

typedef long long int64_t;

int main(void) {
    char buffer[8192];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("ERROR\n");
        return 0;
    }

    size_t len = strlen(buffer);
    if (len == 0) {
        printf("ERROR\n");
        return 0;
    }

    // Remove trailing newline
    while (len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r')) {
        buffer[--len] = '\0';
    }

    int64_t stack[MAX_STACK_SIZE];
    int sp = 0; // stack pointer, points to next free slot

    char *ptr = buffer;
    while (*ptr != '\0') {
        if (isspace((unsigned char)*ptr)) {
            ptr++;
            continue;
        }

        // Check for operator
        if (*ptr == '+' || *ptr == '-' || *ptr == '*') {
            // Pop two operands
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64_t b = stack[--sp];
            int64_t a = stack[--sp];
            int64_t result;

            if (*ptr == '+') {
                result = a + b;
            } else if (*ptr == '-') {
                result = a - b;
            } else if (*ptr == '*') {
                result = a * b;
            } else {
                printf("ERROR\n");
                return 0;
            }

            // Check for overflow (simplified check)
            if (*ptr == '+') {
                if ((a > 0 && b > 0 && a > LLONG_MAX - b) ||
                    (a < 0 && b < 0 && a < LLONG_MIN - b)) {
                    printf("ERROR\n");
                    return 0;
                }
            } else if (*ptr == '-') {
                if ((a > 0 && b < 0 && a > LLONG_MAX + b) ||
                    (a < 0 && b > 0 && a < LLONG_MIN + b)) {
                    printf("ERROR\n");
                    return 0;
                }
            } else if (*ptr == '*') {
                // Check for overflow in multiplication
                if ((b != 0) && (a > LLONG_MAX / b || a < LLONG_MIN / b)) {
                    printf("ERROR\n");
                    return 0;
                }
            }

            stack[sp++] = result;
            ptr++;
            continue;
        }

        // Parse integer
        if (!isdigit((unsigned char)*ptr) && *ptr != '+') {
            printf("ERROR\n");
            return 0;
        }

        char *endptr;
        long long val = strtol(ptr, &endptr, 10);

        // Check if conversion stopped at a non-digit (shouldn't happen with proper input)
        // But we need to ensure the token was fully consumed and valid
        if (endptr == ptr) {
            printf("ERROR\n");
            return 0;
        }

        // Ensure no extra characters after the number
        if (*endptr != '\0' && !isspace((unsigned char)*endptr)) {
            printf("ERROR\n");
            return 0;
        }

        if (sp >= MAX_STACK_SIZE) {
            printf("ERROR\n");
            return 0;
        }

        stack[sp++] = val;
        ptr = endptr;
    }

    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }

    printf("%lld\n", stack[0]);

    return 0;
}
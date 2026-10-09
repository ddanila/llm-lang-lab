#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char token[20];
    long long stack[200];
    int top = 0; // points to next free slot

    while (scanf("%19s", token) == 1) {
        if (token[0] == '+' || token[0] == '-' || token[0] == '*') {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[top - 1];
            long long a = stack[top - 2];
            top -= 2;

            if (token[0] == '+') {
                stack[top++] = a + b;
            } else if (token[0] == '-') {
                stack[top++] = a - b;
            } else if (token[0] == '*') {
                stack[top++] = a * b;
            }
        } else {
            // Parse integer
            char *endptr;
            long long val = strtol(token, &endptr, 10);

            // Check for trailing garbage
            if (*endptr != '\0') {
                printf("ERROR\n");
                return 0;
            }

            // Check if all characters were digits (allowing leading +/-)
            size_t len = strlen(token);
            int has_sign = (token[0] == '+' || token[0] == '-');
            if (!has_sign) {
                for (size_t i = 0; i < len; i++) {
                    if (!isdigit((unsigned char)token[i])) {
                        printf("ERROR\n");
                        return 0;
                    }
                }
            } else {
                // Check that after sign, rest are digits
                for (size_t i = 1; i < len; i++) {
                    if (!isdigit((unsigned char)token[i])) {
                        printf("ERROR\n");
                        return 0;
                    }
                }
            }

            stack[top++] = val;
        }
    }

    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }

    return 0;
}
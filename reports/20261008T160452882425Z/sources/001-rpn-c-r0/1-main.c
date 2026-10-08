#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int main(void) {
    char buf[2048];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 0;
    }

    int stack[200];
    int sp = 0;  // stack pointer, number of elements on stack

    for (char *p = buf; ; ) {
        // Skip whitespace
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0' || *p == '\n') break;

        char op[64];
        int n = 0;
        for (char *q = p; *q && !isspace((unsigned char)*q) && n < 63; q++) {
            op[n++] = *q;
        }
        op[n] = '\0';

        // Parse and validate integer or operator
        if (n == 0) continue; // Should not happen after whitespace skipping

        if (op[0] == '+') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long left = stack[--sp];
            long long right = stack[--sp];
            long long res = left + right;
            // Check for overflow
            if (res > LLONG_MAX || res < LLONG_MIN) {
                printf("ERROR\n");
                return 0;
            }
            stack[sp++] = (int)(res);
        } else if (op[0] == '-') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long left = stack[--sp];
            long long right = stack[--sp];
            long long res = left - right;
            if (res > LLONG_MAX || res < LLONG_MIN) {
                printf("ERROR\n");
                return 0;
            }
            stack[sp++] = (int)(res);
        } else if (op[0] == '*') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long left = stack[--sp];
            long long right = stack[--sp];
            // Check for overflow before multiplication
            if (right != 0 && (left > LLONG_MAX / right || left < LLONG_MIN / right)) {
                printf("ERROR\n");
                return 0;
            }
            long long res = left * right;
            stack[sp++] = (int)(res);
        } else {
            // Must be an integer
            char *endptr;
            errno = 0;
            long long val = strtoll(op, &endptr, 10);
            if (errno != 0 || endptr == op) {
                printf("ERROR\n");
                return 0;
            }
            // Check for overflow
            if (val > LLONG_MAX || val < LLONG_MIN) {
                printf("ERROR\n");
                return 0;
            }
            stack[sp++] = (int)(val);
        }

        p += n;
    }

    if (sp != 1) {
        printf("ERROR\n");
    } else {
        printf("%d\n", stack[0]);
    }

    return 0;
}
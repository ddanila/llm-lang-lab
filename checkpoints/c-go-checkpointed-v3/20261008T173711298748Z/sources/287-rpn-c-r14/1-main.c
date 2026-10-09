#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

typedef long long int64;

int main(void) {
    char buffer[8192];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    if (len == 0) {
        printf("ERROR\n");
        return 0;
    }

    int tokens[MAX_TOKENS];
    int token_count = 0;
    char *p = buffer;

    while (*p && token_count < MAX_TOKENS) {
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        if (!isalnum((unsigned char)*p) && *p != '+' && *p != '-' && *p != '*') {
            printf("ERROR\n");
            return 0;
        }

        // Check for valid integer or operator token
        int is_op = 0;
        if (*p == '+' || *p == '-' || *p == '*') {
            is_op = 1;
        }

        size_t start = p - buffer;
        if (is_op) {
            // Operator: single character
            tokens[token_count] = 0; // Mark as operator, index doesn't matter
            token_count++;
            p++;
            continue;
        } else {
            // Number: parse digits
            size_t end = start;
            while (end < len && !isspace((unsigned char)buffer[end]) && isdigit((unsigned char)buffer[end])) {
                end++;
            }
            if (end == start) {
                // No digit found after non-digit/non-space start - invalid
                printf("ERROR\n");
                return 0;
            }

            int64 value = 0;
            int neg = 0;
            char *num_start = &buffer[start];
            if (*num_start == '+' || *num_start == '-') {
                if (*(num_start + 1) == '\0') {
                    printf("ERROR\n");
                    return 0;
                }
                if (*num_start == '-') neg = 1;
                num_start++;
            }
            
            // Parse number
            errno = 0;
            char *endptr;
            value = strtoll(num_start, &endptr, 10);
            if (errno != 0 || endptr == num_start) {
                printf("ERROR\n");
                return 0;
            }

            tokens[token_count] = (int)value; // Store as int64 in int array for simplicity
            token_count++;
            p = &buffer[end];
            continue;
        }
    }

    if (token_count == 0) {
        printf("ERROR\n");
        return 0;
    }

    int64 stack[STACK_SIZE];
    int sp = 0; // stack pointer, points to next free slot

    for (int i = 0; i < token_count; i++) {
        if (tokens[i] == 0) { // Operator
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[sp - 1];
            int64 a = stack[sp - 2];
            sp -= 2;
            
            switch (tokens[i]) {
                case 1: // +
                    stack[++sp] = a + b;
                    break;
                case 2: // -
                    stack[++sp] = a - b;
                    break;
                case 3: // *
                    stack[++sp] = a * b;
                    break;
            }
        } else {
            if (sp >= STACK_SIZE) {
                printf("ERROR\n");
                return 0;
            }
            stack[sp++] = tokens[i];
        }
    }

    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }

    printf("%lld\n", stack[0]);
    return 0;
}
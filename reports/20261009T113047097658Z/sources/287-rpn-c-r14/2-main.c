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

    int token_type[MAX_TOKENS]; // 0 = number, 1 = +, 2 = -, 3 = *
    int64 tokens[MAX_TOKENS];
    int token_count = 0;
    char *p = buffer;

    while (*p && token_count < MAX_TOKENS) {
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        
        size_t start = p - buffer;
        size_t end = start;
        
        // Skip non-digit, non-operator characters -> error
        while (end < len && !isspace((unsigned char)buffer[end])) {
            if (isdigit((unsigned char)buffer[end]) || 
                buffer[end] == '+' || buffer[end] == '-' || buffer[end] == '*') {
                end++;
            } else {
                // Invalid character
                printf("ERROR\n");
                return 0;
            }
        }

        if (end == start) {
            // No valid token found
            printf("ERROR\n");
            return 0;
        }

        // Parse the token
        char *num_start = &buffer[start];
        
        // Check for operator first (single character operators)
        if (*num_start == '+' || *num_start == '-' || *num_start == '*') {
            if (*(num_start + 1) != '\0' && end > start + 1) {
                // Multi-character operator - invalid
                printf("ERROR\n");
                return 0;
            }
            token_type[token_count] = (*num_start == '+' ? 1 : (*num_start == '-' ? 2 : 3));
            token_count++;
            p = &buffer[end];
            continue;
        }

        // Must be a number
        int64 value = 0;
        int neg = 0;
        
        if (*num_start == '+' || *num_start == '-') {
            if (*(num_start + 1) == '\0') {
                printf("ERROR\n");
                return 0;
            }
            if (*num_start == '-') neg = 1;
            num_start++;
        }
        
        // Parse digits
        char *endptr;
        errno = 0;
        value = strtoll(num_start, &endptr, 10);
        if (errno != 0 || endptr == num_start) {
            printf("ERROR\n");
            return 0;
        }

        token_type[token_count] = 0; // number
        tokens[token_count] = value;
        token_count++;
        p = &buffer[end];
        continue;
    }

    if (token_count == 0) {
        printf("ERROR\n");
        return 0;
    }

    int64 stack[STACK_SIZE];
    int sp = 0; // stack pointer, points to next free slot

    for (int i = 0; i < token_count; i++) {
        if (token_type[i] == 1) { // +
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[sp - 1];
            int64 a = stack[sp - 2];
            sp -= 2;
            stack[++sp] = a + b;
        } else if (token_type[i] == 2) { // -
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[sp - 1];
            int64 a = stack[sp - 2];
            sp -= 2;
            stack[++sp] = a - b;
        } else if (token_type[i] == 3) { // *
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[sp - 1];
            int64 a = stack[sp - 2];
            sp -= 2;
            stack[++sp] = a * b;
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
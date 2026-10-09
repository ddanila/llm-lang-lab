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
        
        // Check for operator first (single character operators that are not part of a number)
        // A single + or - or * is an operator if it's not followed by digits
        if (*num_start == '+' || *num_start == '-' || *num_start == '*') {
            // Check if this could be a number (starts with digit after sign)
            if (*(num_start + 1) == '\0' || 
                !isdigit((unsigned char)*(num_start + 1)) ||
                end == start + 1) {
                // Single character operator
                token_type[token_count] = (*num_start == '+' ? 1 : (*num_start == '-' ? 2 : 3));
            } else {
                // It's a number with sign
                char *parse_start = num_start;
                if (*parse_start == '-') parse_start++;
                else if (*parse_start == '+') parse_start++;
                
                char *endptr;
                errno = 0;
                int64 value = strtoll(parse_start, &endptr, 10);
                if (errno != 0 || endptr == parse_start) {
                    printf("ERROR\n");
                    return 0;
                }
                
                token_type[token_count] = 0; // number
                tokens[token_count] = value;
            }
            p = &buffer[end];
            token_count++;
            continue;
        }

        // Must be a number (starts with digit)
        char *parse_start = num_start;
        char *endptr;
        errno = 0;
        int64 value = strtoll(parse_start, &endptr, 10);
        if (errno != 0 || endptr == parse_start) {
            printf("ERROR\n");
            return 0;
        }

        token_type[token_count] = 0; // number
        tokens[token_count] = value;
        p = &buffer[end];
        token_count++;
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
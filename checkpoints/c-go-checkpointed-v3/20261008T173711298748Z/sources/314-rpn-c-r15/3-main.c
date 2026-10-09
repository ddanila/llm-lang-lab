#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

typedef long long int64;

int main(void) {
    char buffer[1 << 20];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    size_t len = strlen(buffer);
    
    // Remove trailing newline/carriage return but keep empty buffer valid
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[--len] = '\0';
    }

    int64 stack[2000];
    int sp = 0; 

    const char *p = buffer;
    while (p < buffer + len) {
        // Skip whitespace
        while (p < buffer + len && isspace((unsigned char)*p)) {
            p++;
        }
        if (p >= buffer + len) break;

        // Parse token
        int64 val = 0;
        
        if (*p == '+' || *p == '-' || *p == '*') {
            char op = *p;
            p++;
            
            // Pop right operand
            if (sp <= 0) {
                printf("ERROR\n");
                return 0;
            }
            int64 right = stack[--sp];
            
            // Pop left operand
            if (sp <= 0) {
                printf("ERROR\n");
                return 0;
            }
            int64 left = stack[--sp];
            
            int64 result;
            switch (op) {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '*':
                    result = left * right;
                    break;
                default:
                    printf("ERROR\n");
                    return 0;
            }
            
            stack[sp++] = result;
        } else {
            // Parse integer
            int sign = 1;
            if (*p == '+' || *p == '-') {
                sign = (*p == '-') ? -1 : 1;
                p++;
            }
            
            // Must have at least one digit
            if (p >= buffer + len) {
                printf("ERROR\n");
                return 0;
            }
            
            errno = 0;
            char *endptr;
            val = strtoll(p, &endptr, 10);
            
            if (errno != 0 || endptr == p) {
                printf("ERROR\n");
                return 0;
            }
            
            // Check that no extra characters remain before next token or end
            while (endptr < buffer + len && isspace((unsigned char)*endptr)) {
                endptr++;
            }
            
            if (endptr != p) {
                printf("ERROR\n");
                return 0;
            }
            
            val *= sign;
            stack[sp++] = val;
        }
    }

    // Final check: exactly one value on stack
    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }

    printf("%lld\n", stack[0]);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 1024

int main(void) {
    char buffer[1 << 20];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("ERROR\n");
        return 0;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    if (len > 0 && buffer[len - 1] == '\r') {
        buffer[len - 1] = '\0';
        len--;
    }

    long long *stack = malloc(STACK_SIZE * sizeof(long long));
    if (!stack) {
        printf("ERROR\n");
        return 0;
    }
    
    int sp = 0;
    size_t pos = 0;
    
    while (pos < len) {
        // Skip whitespace
        while (pos < len && (buffer[pos] == ' ' || buffer[pos] == '\t' || buffer[pos] == '\n')) {
            pos++;
        }
        
        if (pos >= len) break;

        // Extract token
        size_t token_start = pos;
        while (pos < len && !isspace((unsigned char)buffer[pos])) {
            pos++;
        }
        size_t token_len = pos - token_start;
        char *token = &buffer[token_start];

        // Check if token is an operator (+, -, *)
        int is_operator = 0;
        if (token_len == 1) {
            if (token[0] == '+' || token[0] == '-' || token[0] == '*') {
                is_operator = 1;
            }
        } else {
            // Check if it's a valid integer
            int valid_int = 1;
            for (size_t i = 0; i < token_len; i++) {
                if (!isdigit((unsigned char)token[i])) {
                    valid_int = 0;
                    break;
                }
            }
            
            if (!valid_int) {
                printf("ERROR\n");
                free(stack);
                return 0;
            }
            
            // Parse the integer
            long long num = 0;
            int sign = 1;
            for (size_t i = 0; i < token_len; i++) {
                if (token[i] == '+') {
                    // skip, no sign change needed
                } else if (token[i] == '-') {
                    sign = -1;
                } else {
                    num = num * 10 + (token[i] - '0');
                }
            }
            num *= sign;
            
            // Push to stack
            if (sp >= STACK_SIZE) {
                printf("ERROR\n");
                free(stack);
                return 0;
            }
            stack[sp++] = num;
        } else {
            // Invalid token (not operator, not valid integer)
            printf("ERROR\n");
            free(stack);
            return 0;
        }

        // If we have an operator, check for enough operands and apply
        if (is_operator) {
            if (sp < 2) {
                printf("ERROR\n");
                free(stack);
                return 0;
            }
            
            long long left = stack[sp - 2];
            long long right = stack[sp - 1];
            sp -= 2;
            
            if (token[0] == '+') {
                stack[sp++] = left + right;
            } else if (token[0] == '-') {
                stack[sp++] = left - right;
            } else if (token[0] == '*') {
                stack[sp++] = left * right;
            }
        }
    }

    // Check final stack size
    if (sp != 1) {
        printf("ERROR\n");
        free(stack);
        return 0;
    }

    printf("%lld\n", stack[0]);
    free(stack);
    return 0;
}
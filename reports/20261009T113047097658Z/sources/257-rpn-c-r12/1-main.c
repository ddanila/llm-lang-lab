#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    long long stack[200];
    int top = 0; // points to next free slot
    
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    char *token = strtok(buffer, " \t\n\r");
    while (token != NULL) {
        if (*token == '+' || *token == '-' || *token == '*') {
            // Pop right operand then left operand
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long right = stack[top - 1];
            long long left = stack[top - 2];
            top -= 2;
            
            switch (*token) {
                case '+':
                    stack[top++] = left + right;
                    break;
                case '-':
                    stack[top++] = left - right;
                    break;
                case '*':
                    stack[top++] = left * right;
                    break;
            }
        } else {
            // Parse integer
            char *endptr;
            long long val = strtoll(token, &endptr, 10);
            
            // Check if entire token was consumed and no invalid chars
            if (*endptr != '\0') {
                printf("ERROR\n");
                return 0;
            }
            
            // Check for optional leading +/- followed by at least one digit
            // strtoll handles this, but we need to ensure the sign is valid
            
            stack[top++] = val;
        }
        
        token = strtok(NULL, " \t\n\r");
    }
    
    if (top != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
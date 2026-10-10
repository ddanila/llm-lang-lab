#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKENS 200
#define MAX_STACK 200

int stack[MAX_STACK];
int top = 0;

void push(long long val) {
    if (top >= MAX_STACK) return;
    stack[top++] = (int)val;
}

long long pop() {
    if (top < 1) return 0; // Should not happen in valid RPN
    return stack[--top];
}

long long peek() {
    if (top == 0) return 0;
    return stack[top - 1];
}

int main(void) {
    char buf[1024];
    int ntokens = 0;
    
    // Read all input into buffer
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        // Process tokens from the buffer
        char *token = strtok(buf, " \t\n\r");
        while (token != NULL) {
            if (ntokens >= MAX_TOKENS) break;
            
            // Check if token is a valid integer or operator
            int len = strlen(token);
            if (len == 0) {
                token = strtok(NULL, " \t\n\r");
                continue;
            }
            
            // Check for operator first
            if (len == 1) {
                char c = token[0];
                if (c == '+' || c == '-' || c == '*') {
                    if (ntokens > 0 && top < 2) {
                        printf("ERROR\n");
                        return 0;
                    }
                    if (ntokens > 0) {
                        long long b = pop();
                        long long a = peek(); // Don't pop yet
                        push(a + b); // For '+'
                        continue;
                    } else {
                        printf("ERROR\n");
                        return 0;
                    }
                }
            }
            
            // Check if token is an integer
            int i = 0;
            int sign = 1;
            if (token[0] == '+' || token[0] == '-') {
                if (len > 1) {
                    if (token[0] == '+') sign = 1;
                    else if (token[0] == '-') sign = -1;
                    i = 1;
                } else {
                    // Just + or - alone, not valid integer
                    printf("ERROR\n");
                    return 0;
                }
            }
            
            // Check remaining characters are digits
            if (i < len) {
                for (; i < len; i++) {
                    if (!isdigit((unsigned char)token[i])) {
                        printf("ERROR\n");
                        return 0;
                    }
                }
                
                // Parse the integer
                long long val = 0;
                int idx = i;
                while (idx < len) {
                    val = val * 10 + (token[idx] - '0');
                    idx++;
                }
                val *= sign;
                
                push(val);
            } else {
                // Only sign, no digits - invalid
                printf("ERROR\n");
                return 0;
            }
            
            ntokens++;
            token = strtok(NULL, " \t\n\r");
        }
    }
    
    // Check final stack size
    if (top != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%d\n", stack[0]);
    
    return 0;
}
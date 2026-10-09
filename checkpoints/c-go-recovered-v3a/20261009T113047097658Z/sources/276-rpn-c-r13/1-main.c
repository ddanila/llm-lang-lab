#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_TOKENS 200
#define STACK_SIZE 256

int main(void) {
    char buf[MAX_TOKENS][128];
    int count = 0;
    
    // Read tokens until EOF or newline
    char c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (isspace(c)) continue;
        if (count >= MAX_TOKENS) break;
        
        int in_token = 0;
        for (int i = count; i < MAX_TOKENS && (c = getchar()) != EOF; i++) {
            if (isspace(c)) {
                buf[count][i - count] = '\0';
                count++;
                break;
            } else {
                buf[count][i - count] = c;
                in_token = 1;
            }
        }
        
        // Handle end of file without newline
        if (c == EOF && in_token) {
            buf[count][0] = '\0';
            count++;
        }
    }
    
    if (count == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    // Stack for RPN evaluation
    long long stack[STACK_SIZE];
    int sp = 0; // stack pointer
    
    for (int i = 0; i < count; i++) {
        const char *token = buf[i];
        
        if (strlen(token) == 0) continue;
        
        // Check if operator
        if (*token == '+' || *token == '-' || *token == '*') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            
            long long right = stack[sp - 1];
            long long left = stack[sp - 2];
            sp -= 2;
            
            if (*token == '+') {
                stack[++sp - 1] = left + right;
            } else if (*token == '-') {
                stack[++sp - 1] = left - right;
            } else if (*token == '*') {
                stack[++sp - 1] = left * right;
            }
        } else {
            // Must be integer
            char *endptr;
            long long val = strtoll(token, &endptr, 10);
            
            // Check for invalid characters or no digits
            if (*token == '+' || *token == '-') {
                // Leading sign is OK, but must have at least one digit after
                char *p = token + 1;
                if (strlen(p) == 0 || !isdigit((unsigned char)*p)) {
                    printf("ERROR\n");
                    return 0;
                }
            } else if (*token == '\0') {
                // Empty token after stripping whitespace - shouldn't happen
                printf("ERROR\n");
                return 0;
            }
            
            stack[sp++] = val;
        }
    }
    
    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
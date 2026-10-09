#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

int main(void) {
    long long stack[200];
    int top = 0;  // Stack is empty when top == 0
    
    char token[65];
    
    while (scanf("%64s", token) == 1) {
        if (token[0] == '\0') continue;
        
        if (strlen(token) > 20) {
            printf("ERROR\n");
            return 0;
        }
        
        long long val;
        int is_op = 0;
        
        // Check for operator
        const char *ops = "+-*";
        for (int i = 0; ops[i]; i++) {
            if (strcmp(token, &ops[i]) == 0) {
                if (top < 2) {
                    printf("ERROR\n");
                    return 0;
                }
                val = stack[top - 1];
                top--;
                long long right = stack[top - 1];
                top--;
                
                if (ops[i] == '+') {
                    stack[top] = val + right;
                } else if (ops[i] == '-') {
                    stack[top] = val - right;
                } else if (ops[i] == '*') {
                    stack[top] = val * right;
                }
                continue;
            }
        }
        
        // Must be an integer token
        int sign = 1;
        const char *p = token;
        
        if (*p == '+') p++;
        else if (*p == '-') {
            sign = -1;
            p++;
        }
        
        if (*p == '\0') {
            printf("ERROR\n");
            return 0;
        }
        
        // Check for non-digit characters
        while (*p) {
            if (!isdigit((unsigned char)*p)) {
                printf("ERROR\n");
                return 0;
            }
            p++;
        }
        
        val = sign * atoll(token);
        
        if (top >= 200) {
            printf("ERROR\n");
            return 0;
        }
        stack[top++] = val;
    }
    
    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }
    
    return 0;
}
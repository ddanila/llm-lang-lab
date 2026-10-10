#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 10000

long long stack[STACK_SIZE];
int top = 0;

int is_operator(const char *token) {
    if (strlen(token) != 1) return 0;
    return token[0] == '+' || token[0] == '-' || token[0] == '*';
}

long long eval_integer(const char *token) {
    const char *p = token;
    
    int sign = 1;
    if (*p == '+') {
        p++;
    } else if (*p == '-') {
        sign = -1;
        p++;
    }
    
    if (!isdigit(*p)) return 0; // Not a valid integer
    
    long long val = 0;
    while (isdigit(*p)) {
        val = val * 10 + (*p - '0');
        p++;
    }
    
    return sign * val;
}

int main() {
    char buffer[MAX_TOKENS][256];
    int count = 0;
    
    // Read all tokens
    char line[4096];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        char *p = line;
        char *token = strtok(p, " \t\n\r");
        while (token != NULL) {
            if (count < MAX_TOKENS) {
                strcpy(buffer[count], token);
                count++;
            }
            token = strtok(NULL, " \t\n\r");
        }
    }
    
    // Process tokens
    for (int i = 0; i < count; i++) {
        const char *token = buffer[i];
        
        if (is_operator(token)) {
            // It's an operator
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long right = stack[top - 1];
            long long left = stack[top - 2];
            top -= 2;
            
            switch (token[0]) {
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
            // Try to parse as integer
            long long val = eval_integer(token);
            
            if (val == 0) {
                // Invalid token (empty or non-numeric)
                printf("ERROR\n");
                return 0;
            }
            
            stack[top++] = val;
        }
    }
    
    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }
    
    return 0;
}
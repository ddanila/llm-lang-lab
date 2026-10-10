#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 10000

int stack[STACK_SIZE];
int top = 0;

long long eval_token(const char *token) {
    if (strlen(token) == 0) return 0;
    
    int sign = 1;
    const char *p = token;
    
    if (*p == '+' || *p == '-') {
        if (*p == '-') {
            sign = -1;
            p++;
        } else if (*p == '+') {
            p++;
        }
    }
    
    if (!isdigit(*p)) return 0;
    
    long long val = 0;
    while (isdigit(*p)) {
        val = val * 10 + (*p - '0');
        p++;
    }
    
    return sign * val;
}

int is_operator(const char *token) {
    if (strlen(token) != 1) return 0;
    return token[0] == '+' || token[0] == '-' || token[0] == '*';
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
        long long val = eval_token(buffer[i]);
        
        if (val != 0 && is_operator(buffer[i])) {
            // It's an operator
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long right = stack[top - 1];
            long long left = stack[top - 2];
            top -= 2;
            
            switch (buffer[i][0]) {
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
        } else if (val == 0 && strlen(buffer[i]) > 0) {
            // Invalid token (not an operator and not a valid integer)
            printf("ERROR\n");
            return 0;
        } else {
            // Valid integer
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
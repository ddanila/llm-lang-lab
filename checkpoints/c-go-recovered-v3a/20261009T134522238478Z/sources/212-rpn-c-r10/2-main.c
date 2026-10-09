#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKENS 200
#define STACK_SIZE 10000

typedef long long int64;

int main(void) {
    char buf[100];
    char tokens[MAX_TOKENS][100];
    int n = 0;
    
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        char *p = buf;
        // Skip leading whitespace
        while (*p && isspace((unsigned char)*p)) p++;
        
        if (*p == '\0') continue;
        
        // Check for operators
        if (strncmp(p, "+", 1) == 0 && p[1] == '\0') {
            strcpy(tokens[n], "+");
            n++;
            continue;
        }
        if (strncmp(p, "-", 1) == 0 && p[1] == '\0') {
            strcpy(tokens[n], "-");
            n++;
            continue;
        }
        if (strncmp(p, "*", 1) == 0 && p[1] == '\0') {
            strcpy(tokens[n], "*");
            n++;
            continue;
        }
        
        // Try to parse as integer
        char *endptr;
        int64 val = strtoll(p, &endptr, 10);
        
        if (endptr == p || (*endptr != '\0' && !isspace((unsigned char)*endptr))) {
            // Invalid token
            printf("ERROR\n");
            return 0;
        }
        
        char *tok_str = malloc(20);
        if (!tok_str) {
            printf("ERROR\n");
            return 0;
        }
        sprintf(tok_str, "%lld", val);
        strncpy(tokens[n], tok_str, 19);
        tokens[n][19] = '\0';
        free(tok_str);
        n++;
    }
    
    if (n == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    // RPN evaluation
    int64 stack[STACK_SIZE];
    int top = 0;
    
    for (int i = 0; i < n; i++) {
        char *tok = tokens[i];
        
        if (strcmp(tok, "+") == 0) {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[top - 1];
            int64 a = stack[top - 2];
            stack[top - 2] = a + b;
            top--;
        } else if (strcmp(tok, "-") == 0) {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[top - 1];
            int64 a = stack[top - 2];
            stack[top - 2] = a - b;
            top--;
        } else if (strcmp(tok, "*") == 0) {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[top - 1];
            int64 a = stack[top - 2];
            stack[top - 2] = a * b;
            top--;
        } else {
            // Should not happen if input validation is correct
            printf("ERROR\n");
            return 0;
        }
    }
    
    if (top != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
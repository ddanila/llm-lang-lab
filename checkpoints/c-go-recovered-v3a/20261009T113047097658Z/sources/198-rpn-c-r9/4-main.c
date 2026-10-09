#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 512

long long stack[STACK_SIZE];
int top = -1;

int is_operator(const char *s) {
    return (strcmp(s, "+") == 0) || (strcmp(s, "-") == 0) || (strcmp(s, "*") == 0);
}

int parse_int(const char *s, long long *val) {
    const char *p = s;
    if (*p == '+' || *p == '-') p++;
    if (!isdigit((unsigned char)*p)) return 0;
    long long v = 0;
    while (isdigit((unsigned char)*p)) {
        v = v * 10 + (*p - '0');
        p++;
    }
    if (s[0] == '-') v = -v;
    *val = v;
    return 1;
}

int main(void) {
    char buf[MAX_TOKENS + 1];
    int n = 0;
    
    while (fgets(buf, sizeof(buf), stdin) != NULL && n < MAX_TOKENS) {
        // Remove newline if present
        size_t len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n') buf[--len] = '\0';
        
        char *p = buf;
        while (*p != '\0' && n < MAX_TOKENS) {
            // Skip whitespace
            while (*p == ' ' || *p == '\t' || *p == '\r') p++;
            
            if (*p == '\0') break;
            
            char token[64];
            int len = 0;
            while (len < sizeof(token) - 1 && !isspace((unsigned char)*p)) {
                token[len++] = *p++;
            }
            token[len] = '\0';
            
            // Check for invalid characters (except digits, +, -)
            if (!isdigit((unsigned char)token[0]) && token[0] != '+' && token[0] != '-') {
                printf("ERROR\n");
                return 0;
            }
            
            if (is_operator(token)) {
                if (top < 1) {
                    printf("ERROR\n");
                    return 0;
                }
                long long right = stack[top--];
                long long left = stack[top--];
                
                if (*token == '+') {
                    stack[++top] = left + right;
                } else if (*token == '-') {
                    stack[++top] = left - right;
                } else if (*token == '*') {
                    stack[++top] = left * right;
                }
            } else {
                long long val;
                if (!parse_int(token, &val)) {
                    printf("ERROR\n");
                    return 0;
                }
                stack[++top] = val;
            }
            
            n++;
        }
    }
    
    if (n == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    if (top != 0) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
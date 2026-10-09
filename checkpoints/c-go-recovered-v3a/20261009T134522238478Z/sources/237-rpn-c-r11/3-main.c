#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

typedef long long int64;
int64 stack[MAX_STACK_SIZE];
int top = -1;

void push(int64 val) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++top] = val;
}

int64 pop() {
    if (top < 0) return 0; // Should not happen for valid ops
    int64 val = stack[top--];
    return val;
}

int main() {
    int64 stack[MAX_STACK_SIZE];
    int top = -1;
    char buf[256];
    int ntokens = 0;
    
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        // Remove trailing newline
        size_t len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n') {
            buf[len-1] = '\0';
            len--;
        }
        
        char *token = strtok(buf, " \t\n");
        while (token != NULL) {
            long long val;
            
            // Check if it's an operator first
            if (strcmp(token, "+") == 0) {
                if (top < 1) {
                    printf("ERROR\n");
                    return 0;
                }
                int64 b = pop();
                int64 a = pop();
                push(a + b);
            } else if (strcmp(token, "-") == 0) {
                if (top < 1) {
                    printf("ERROR\n");
                    return 0;
                }
                int64 b = pop();
                int64 a = pop();
                push(a - b);
            } else if (strcmp(token, "*") == 0) {
                if (top < 1) {
                    printf("ERROR\n");
                    return 0;
                }
                int64 b = pop();
                int64 a = pop();
                push(a * b);
            } else if (isdigit((unsigned char)*token)) {
                // Parse number - handle optional leading + or -
                const char *p = token;
                long long v = 0;
                while (*p == ' ') p++; // skip spaces
                
                int neg = 0;
                if (*p == '+') {
                    p++;
                } else if (*p == '-') {
                    neg = 1;
                    p++;
                }
                
                if (*p == '\0') continue; // no digits after sign, invalid
                
                while (isdigit((unsigned char)*p)) {
                    v = v * 10 + (*p - '0');
                    p++;
                }
                
                if (neg) v = -v;
                push(v);
            } else {
                // Invalid token (non-digit, non-operator)
                printf("ERROR\n");
                return 0;
            }
            
            ntokens++;
            if (ntokens >= MAX_TOKENS) break;
            
            token = strtok(NULL, " \t\n");
        }
    }
    
    if (top != 0) {
        printf("ERROR\n");
        return 0;
    }
    
    int64 result = stack[0];
    printf("%lld\n", result);
    return 0;
}
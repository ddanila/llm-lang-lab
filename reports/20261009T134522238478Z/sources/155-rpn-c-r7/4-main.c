#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

long long stack[MAX_STACK_SIZE];
int sp = 0;

int parse_int(const char *s) {
    const char *p = s;
    int sign = 1;
    if (*p == '+' || *p == '-') {
        if (*p == '-') sign = -1;
        p++;
    }
    if (!isdigit(*p)) return 0;
    long long val = 0;
    while (isdigit(*p)) {
        val = val * 10 + (*p - '0');
        p++;
    }
    return sign * val;
}

void push(long long v) {
    if (sp < MAX_STACK_SIZE) stack[sp++] = v;
}

long long pop() {
    return stack[--sp];
}

int main(void) {
    char buf[MAX_TOKENS * 10];
    int len = 0;
    
    // Read all input into buffer
    while (len < MAX_TOKENS * 10 && getchar() != EOF) {
        if (len >= MAX_TOKENS * 10) break;
        char c = getchar();
        buf[len++] = c;
    }
    
    int pos = 0;
    
    while (pos < len) {
        // Skip whitespace
        while (pos < len && (buf[pos] == ' ' || buf[pos] == '\n' || buf[pos] == '\t' || buf[pos] == '\r')) {
            pos++;
        }
        
        if (pos >= len) break;
        
        char op = buf[pos];
        
        // Check for operator (+, -, *)
        if (op == '+' || op == '-' || op == '*') {
            int left, right;
            
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            
            right = stack[--sp];
            left = stack[--sp];
            
            long long result;
            switch (op) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                default: result = 0; break;
            }
            
            push(result);
        } else if (isdigit(op)) {
            // This is a number token (no leading +/- since that would be handled as operator)
            int val = parse_int(buf + pos);
            push(val);
        } else {
            // Invalid character
            printf("ERROR\n");
            return 0;
        }
        
        // Move past the token - skip all non-whitespace characters
        while (pos < len && buf[pos] != ' ' && buf[pos] != '\n' && buf[pos] != '\t' && buf[pos] != '\r') {
            pos++;
        }
    }
    
    if (sp != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }
    
    return 0;
}
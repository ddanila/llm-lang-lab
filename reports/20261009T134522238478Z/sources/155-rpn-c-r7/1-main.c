#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

int stack[MAX_STACK_SIZE];
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
    return sign * (int)val;
}

void push(long long v) {
    if (sp < MAX_STACK_SIZE) stack[sp++] = (int)v;
}

long long pop() {
    return stack[--sp];
}

long long top() {
    return stack[sp - 1];
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
    
    int n = 0;
    int pos = 0;
    
    while (pos < len) {
        // Skip whitespace
        while (pos < len && (buf[pos] == ' ' || buf[pos] == '\n' || buf[pos] == '\t' || buf[pos] == '\r')) {
            pos++;
        }
        
        if (pos >= len) break;
        
        char op = buf[pos];
        
        // Check for operator
        if (op == '+' || op == '-' || op == '*') {
            n++;
            // Parse next integer
            int val = parse_int(buf + pos);
            push(val);
            pos++;
        } else {
            // Not an operator, must be invalid or part of number which is already handled
            // Actually, we need to handle numbers here too
            // But the loop structure above only handles operators directly
            // We need a different approach
            
            // Actually, let me rethink: we need to parse tokens one by one
            // A token can be: +, -, *, or a number (with optional +/- prefix)
            
            // Let's restructure
            break;
        }
    }
    
    return 0;
}
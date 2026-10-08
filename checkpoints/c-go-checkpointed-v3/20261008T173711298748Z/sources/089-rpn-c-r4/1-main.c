#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char *tokens[205];
    int count = 0;
    char c;
    
    // Read all input into a buffer first to tokenize properly
    char buf[65536] = {0};
    size_t len = 0;
    
    while ((c = getchar()) != EOF) {
        if (len + 1 >= sizeof(buf)) break;
        buf[len++] = c;
    }
    
    // Tokenize
    char *p = buf;
    int i = 0;
    while (*p && i < 205) {
        // Skip whitespace
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;
        
        tokens[i] = p;
        i++;
        
        // Find end of token
        char *end = p + 1;
        while (*end && !isspace((unsigned char)*end) && *end != '\n' && *end != '\r') {
            end++;
        }
        p = end;
    }
    
    // Process RPN
    long long stack[205];
    int top = 0; // Stack size
    
    for (int k = 0; k < i; k++) {
        char *tok = tokens[k];
        
        if (*tok == '+') {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[top - 1];
            long long a = stack[top - 2];
            stack[top - 2] = a + b;
            top--;
        } else if (*tok == '-') {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[top - 1];
            long long a = stack[top - 2];
            stack[top - 2] = a - b;
            top--;
        } else if (*tok == '*') {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[top - 1];
            long long a = stack[top - 2];
            stack[top - 2] = a * b;
            top--;
        } else {
            // Parse integer
            int sign = 1;
            if (*tok == '+') {
                tok++;
            } else if (*tok == '-') {
                sign = -1;
                tok++;
            }
            
            const char *num = tok;
            while (isdigit((unsigned char)*num)) num++;
            
            // Check for invalid token (no digits after optional sign)
            if (num == tok) {
                printf("ERROR\n");
                return 0;
            }
            
            long long val = 0;
            const char *s = num;
            while (*s) {
                if (!isdigit((unsigned char)*s)) break;
                int d = *s - '0';
                // Check for overflow before multiplying by 10 and adding
                if (val > (LLONG_MAX - d) / 10) {
                    printf("ERROR\n");
                    return 0;
                }
                val = val * 10 + d;
                s++;
            }
            
            stack[top] = val * sign;
            top++;
        }
    }
    
    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }
    
    return 0;
}
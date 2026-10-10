#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int main(void) {
    char buf[65536] = {0};
    size_t len = 0;
    
    // Read all input into a buffer
    while ((len < sizeof(buf) - 1) && (buf[len] = getchar()) != EOF) {
        len++;
    }
    buf[len] = '\0';
    
    // Tokenize and process in one pass
    char *p = buf;
    long long stack[205];
    int top = 0;
    int token_count = 0;
    
    while (*p && token_count < 205) {
        // Skip whitespace
        while (isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;
        
        // Start of a new token
        char *tok_start = p;
        
        // Find end of token
        while (*p && !isspace((unsigned char)*p) && *p != '\n' && *p != '\r') {
            p++;
        }
        
        // Process the token from tok_start to p
        if (tok_start == p) continue; // Empty token
        
        if (*tok_start == '+') {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[top - 1];
            long long a = stack[top - 2];
            stack[top - 2] = a + b;
            top--;
        } else if (*tok_start == '-') {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[top - 1];
            long long a = stack[top - 2];
            stack[top - 2] = a - b;
            top--;
        } else if (*tok_start == '*') {
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
            const char *tok = tok_start;
            
            if (*tok == '+') {
                tok++;
            } else if (*tok == '-') {
                sign = -1;
                tok++;
            }
            
            // Check for invalid token (no digits after optional sign)
            if (*tok == '\0') {
                printf("ERROR\n");
                return 0;
            }
            
            long long val = 0;
            const char *s = tok;
            while (isdigit((unsigned char)*s)) {
                int d = *s - '0';
                // Check for overflow before multiplying by 10 and adding
                if (val > (LONG_MAX - d) / 10) {
                    printf("ERROR\n");
                    return 0;
                }
                val = val * 10 + d;
                s++;
            }
            
            stack[top] = val * sign;
            top++;
        }
        
        token_count++;
    }
    
    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }
    
    return 0;
}
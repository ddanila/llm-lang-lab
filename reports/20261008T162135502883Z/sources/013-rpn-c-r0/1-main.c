#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char *tokens[200];
    int token_count = 0;
    char buffer[1 << 20];
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    
    char *p = buffer;
    while (*p && (token_count < 200)) {
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        
        // Find end of token
        char *start = p;
        while (*p && !isspace((unsigned char)*p)) p++;
        if (!*p) break;
        
        size_t len = (size_t)(p - start);
        if (len == 0) continue;
        
        // Check for invalid token
        int is_valid = 1;
        if (*start == '+' || *start == '-') {
            start++;
            len--;
            if (len == 0) is_valid = 0;
            else if (!isdigit((unsigned char)*start)) is_valid = 0;
        } else if (!isdigit((unsigned char)*start)) {
            is_valid = 0;
        }
        
        if (!is_valid) {
            printf("ERROR\n");
            return 0;
        }
        
        tokens[token_count++] = start;
    }
    
    // Stack
    long long stack[200];
    int sp = 0;
    
    for (int i = 0; i < token_count; i++) {
        const char *t = tokens[i];
        if (*t == '+') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[--sp];
            long long a = stack[--sp];
            stack[sp++] = a + b;
        } else if (*t == '-') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[--sp];
            long long a = stack[--sp];
            stack[sp++] = a - b;
        } else if (*t == '*') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[--sp];
            long long a = stack[--sp];
            stack[sp++] = a * b;
        } else {
            // Parse integer
            char *endptr;
            long long val = strtoll(t, &endptr, 10);
            if (endptr != t + strlen(t)) {
                printf("ERROR\n");
                return 0;
            }
            stack[sp++] = val;
        }
    }
    
    if (sp != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
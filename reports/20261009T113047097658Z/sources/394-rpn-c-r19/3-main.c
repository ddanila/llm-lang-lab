#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char buf[10000];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 0;
    }
    
    int n = strlen(buf);
    int top = 0;
    long long stack[200];
    
    for (int i = 0; i < n; ) {
        // Skip whitespace
        while (i < n && isspace((unsigned char)buf[i])) {
            i++;
        }
        
        if (i >= n) break;
        
        char c = buf[i];
        
        if (c == '+' || c == '-' || c == '*') {
            // This is an operator
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[--top];
            long long a = stack[--top];
            
            if (c == '+') {
                stack[top++] = a + b;
            } else if (c == '-') {
                stack[top++] = a - b;
            } else if (c == '*') {
                stack[top++] = a * b;
            }
        } else if (isdigit((unsigned char)c)) {
            // Parse number with optional sign
            int sign = 1;
            if (c == '+') {
                i++;
                c = buf[i];
            } else if (c == '-') {
                sign = -1;
                i++;
                c = buf[i];
            }
            
            long long val = 0;
            while (i < n && isdigit((unsigned char)buf[i])) {
                val = val * 10 + (buf[i] - '0');
                i++;
            }
            val *= sign;
            
            if (top >= 200) {
                printf("ERROR\n");
                return 0;
            }
            stack[top++] = val;
        } else {
            // Invalid character
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
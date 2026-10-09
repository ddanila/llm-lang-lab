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
        
        if (isdigit((unsigned char)c)) {
            // Parse positive number
            long long val = 0;
            while (i < n && isdigit((unsigned char)buf[i])) {
                val = val * 10 + (buf[i] - '0');
                i++;
            }
            
            if (top >= 200) {
                printf("ERROR\n");
                return 0;
            }
            stack[top++] = val;
        } else if (c == '+' || c == '-') {
            // Could be operator or start of negative number
            // Check if followed by digit(s)
            if (i + 1 < n && isdigit((unsigned char)buf[i+1])) {
                // It's a signed number
                int sign = (c == '-') ? -1 : 1;
                long long val = 0;
                i++; // skip the sign
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
                // It's an operator
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
            }
        } else if (c == '*') {
            // Operator
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[--top];
            long long a = stack[--top];
            
            stack[top++] = a * b;
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
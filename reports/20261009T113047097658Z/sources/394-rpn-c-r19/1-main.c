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
        
        // Parse a token
        int sign = 1;
        if (buf[i] == '+') {
            i++;
            if (i >= n || !isdigit((unsigned char)buf[i])) {
                printf("ERROR\n");
                return 0;
            }
        } else if (buf[i] == '-') {
            sign = -1;
            i++;
            if (i >= n || !isdigit((unsigned char)buf[i])) {
                printf("ERROR\n");
                return 0;
            }
        }
        
        long long val = 0;
        while (i < n && isdigit((unsigned char)buf[i])) {
            val = val * 10 + (buf[i] - '0');
            i++;
        }
        val *= sign;
        
        // Push to stack
        if (top >= 200) {
            printf("ERROR\n");
            return 0;
        }
        stack[top++] = val;
    }
    
    if (top != 1) {
        printf("ERROR\n");
        return 0;
    }
    
    printf("%lld\n", stack[0]);
    return 0;
}
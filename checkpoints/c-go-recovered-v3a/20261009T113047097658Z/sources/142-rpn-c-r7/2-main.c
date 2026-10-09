#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char token[65];  // enough for 64-bit int + sign
    long long stack[205];
    int sp = 0;  // stack pointer, points to next free slot
    
    while (scanf("%63s", token) == 1) {
        if (token[0] == '+' || token[0] == '-' || token[0] == '*') {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            long long b = stack[--sp];
            long long a = stack[--sp];
            if (token[0] == '+') {
                stack[sp++] = a + b;
            } else if (token[0] == '-') {
                stack[sp++] = a - b;
            } else if (token[0] == '*') {
                stack[sp++] = a * b;
            }
        } else {
            // Parse integer
            char *endptr;
            long long val = strtoll(token, &endptr, 10);
            
            // Check for incomplete parsing (should have consumed all characters)
            if (*endptr != '\0') {
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
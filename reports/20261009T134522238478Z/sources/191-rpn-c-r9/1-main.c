#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    int stack[200];
    int top = 0;
    char buf[1024] = {0};
    char *tok;

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 0;
    }

    while ((tok = strtok(NULL, " \t\n\r")) != NULL) {
        int len = strlen(tok);
        int i;
        
        // Check if it's an operator
        if (len == 1) {
            char c = tok[0];
            if (c == '+' || c == '-' || c == '*') {
                if (top < 2) {
                    printf("ERROR\n");
                    return 0;
                }
                int right = stack[top - 1];
                int left = stack[top - 2];
                top -= 2;
                
                if (c == '+') {
                    stack[top] = left + right;
                } else if (c == '-') {
                    stack[top] = left - right;
                } else if (c == '*') {
                    stack[top] = left * right;
                }
            } else {
                printf("ERROR\n");
                return 0;
            }
        } else {
            // Must be an integer
            int val = 0;
            int sign = 1;
            
            if (tok[0] == '+') {
                i = 1;
            } else if (tok[0] == '-') {
                sign = -1;
                i = 1;
            } else {
                i = 0;
            }
            
            // Check for at least one digit after optional sign
            if (i >= len) {
                printf("ERROR\n");
                return 0;
            }
            
            for (; i < len; i++) {
                if (!isdigit((unsigned char)tok[i])) {
                    printf("ERROR\n");
                    return 0;
                }
                val = val * 10 + (tok[i] - '0');
            }
            
            stack[top++] = sign * val;
        }
    }

    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%d\n", stack[0]);
    }

    return 0;
}
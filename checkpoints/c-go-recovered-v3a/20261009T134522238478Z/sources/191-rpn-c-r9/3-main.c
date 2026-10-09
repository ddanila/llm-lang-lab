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
        
        // Check if it's an operator (single character +, -, *)
        if (len == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*')) {
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            int right = stack[top - 1];
            int left = stack[top - 2];
            top -= 2;
            
            if (tok[0] == '+') {
                stack[top] = left + right;
            } else if (tok[0] == '-') {
                stack[top] = left - right;
            } else if (tok[0] == '*') {
                stack[top] = left * right;
            }
        } else {
            // Must be an integer token
            int val = 0;
            int sign = 1;
            
            if (len < 1) {
                printf("ERROR\n");
                return 0;
            }
            
            int idx = 0;
            if (tok[0] == '+') {
                idx = 1;
            } else if (tok[0] == '-') {
                sign = -1;
                idx = 1;
            }
            
            // Check for at least one digit after optional sign
            if (idx >= len) {
                printf("ERROR\n");
                return 0;
            }
            
            for (; idx < len; idx++) {
                if (!isdigit((unsigned char)tok[idx])) {
                    printf("ERROR\n");
                    return 0;
                }
                val = val * 10 + (tok[idx] - '0');
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
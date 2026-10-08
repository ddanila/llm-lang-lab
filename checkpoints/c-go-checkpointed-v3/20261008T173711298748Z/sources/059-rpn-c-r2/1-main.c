#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    long long stack[205];
    int sp = 0; // stack pointer, points to next free slot

    char buf[1024] = {0};
    int total_len = 0;

    // Read all input into a buffer
    while (fgets(buf + total_len, sizeof(buf) - total_len, stdin)) {
        // Remove trailing newline if present
        size_t len = strlen(buf);
        while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
            buf[--len] = '\0';
        }
        total_len = (int)len;
    }

    // Parse tokens and evaluate RPN
    char *p = buf;
    while (*p && total_len > 0) {
        // Skip whitespace
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\0') break;

        long long val;
        int is_op = 0;

        // Check for operator
        if (*p == '+' || *p == '-' || *p == '*') {
            char op_char = *p;
            p++;
            
            // Apply operation
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            
            long long right = stack[sp - 1];
            sp--;
            long long left = stack[sp - 1];
            sp--;
            
            if (op_char == '+') {
                val = left + right;
            } else if (op_char == '-') {
                val = left - right;
            } else if (op_char == '*') {
                val = left * right;
            }
            
            stack[sp++] = val;
            continue;
        }

        // Parse integer (optional leading +/-)
        int sign = 1;
        if (*p == '+' || *p == '-') {
            if (*p == '-') sign = -1;
            p++;
        }
        
        // Must have at least one digit after optional sign
        if (!isdigit((unsigned char)*p)) {
            printf("ERROR\n");
            return 0;
        }

        val = 0;
        while (isdigit((unsigned char)*p)) {
            val = val * 10 + (*p - '0');
            p++;
        }
        
        if (sign == -1) val = -val;
        
        if (sp >= 205) {
            printf("ERROR\n");
            return 0;
        }
        stack[sp++] = val;
    }

    // Check final result
    if (sp != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    long long stack[200];
    int sp = 0; // stack pointer, points to next free slot
    char token[65];
    
    while (1) {
        if (fgets(token, sizeof(token), stdin) == NULL) {
            break;
        }
        
        // Remove newline/carriage return
        size_t len = strlen(token);
        while (len > 0 && (token[len-1] == '\n' || token[len-1] == '\r')) {
            token[--len] = '\0';
        }
        
        // Skip empty lines (though tokens are whitespace-separated)
        if (len == 0) continue;
        
        // Check for leading/trailing whitespace in the token string itself
        size_t i = 0;
        while (i < len && isspace((unsigned char)token[i])) {
            i++;
        }
        size_t j = len - 1;
        while (j >= i && isspace((unsigned char)token[j])) {
            j--;
        }
        
        if (i > j || len == 0) {
            // Token was all whitespace or empty after trimming
            continue;
        }
        
        size_t tok_len = j - i + 1;
        
        // Check for invalid characters
        for (size_t k = i; k <= j; k++) {
            char c = token[k];
            if (!isdigit((unsigned char)c) && c != '+' && c != '-') {
                printf("ERROR\n");
                return 0;
            }
        }
        
        // Parse the number or operator
        size_t start = i;
        
        // Handle sign
        if (token[start] == '+' || token[start] == '-') {
            start++;
            tok_len--;
            
            // Must have at least one digit after sign
            if (start > j) {
                printf("ERROR\n");
                return 0;
            }
        }
        
        // Check for operator
        char op = '\0';
        int is_op = 0;
        
        if (tok_len == 1) {
            if (token[start] == '+' || token[start] == '-' || token[start] == '*') {
                is_op = 1;
                op = token[start];
            } else {
                // Single character that is not a valid operator and not a number
                printf("ERROR\n");
                return 0;
            }
        }
        
        if (is_op) {
            if (sp < 2) {
                printf("ERROR\n");
                return 0;
            }
            
            long long right = stack[sp - 1];
            long long left = stack[sp - 2];
            sp -= 2;
            
            switch (op) {
                case '+':
                    stack[sp++] = left + right;
                    break;
                case '-':
                    stack[sp++] = left - right;
                    break;
                case '*':
                    // Check for overflow before multiplying
                    if (left != 0 && right != 0) {
                        if ((left > 0 && right > 0 && left > LLONG_MAX / right) ||
                            (left < 0 && right < 0 && abs(left) > LLONG_MAX / right)) {
                            printf("ERROR\n");
                            return 0;
                        }
                    }
                    stack[sp++] = left * right;
                    break;
            }
        } else {
            // Parse integer
            char *endptr;
            errno = 0;
            long long val = strtoll(token, &endptr, 10);
            
            if (errno == ERANGE || endptr != token + tok_len) {
                printf("ERROR\n");
                return 0;
            }
            
            if (sp >= 200) {
                printf("ERROR\n");
                return 0;
            }
            stack[sp++] = val;
        }
    }
    
    if (sp != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }
    
    return 0;
}
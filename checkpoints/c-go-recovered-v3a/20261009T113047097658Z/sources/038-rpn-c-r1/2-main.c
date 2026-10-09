#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_TOKENS 200
#define MAX_STACK_SIZE 200

typedef long long int64;

int main(void) {
    char buffer[10 * MAX_TOKENS];
    int r = fread(buffer, 1, sizeof(buffer), stdin);
    if (r == 0) return 0;

    // Tokenize into an array
    int tokens[MAX_TOKENS][256]; // [count][length]
    int token_count = 0;
    char *p = buffer;
    while (*p && n < MAX_TOKENS) {
        if (isspace((unsigned char)*p)) {
            p++;
            continue;
        }
        // Read a non-whitespace token
        char tok[MAX_STACK_SIZE];
        int len = 0;
        while (!isspace((unsigned char)*p) && *p != '\n' && *p != '\r' && len < MAX_STACK_SIZE - 1) {
            tok[len++] = *p++;
        }
        tok[len] = '\0';
        
        if (len == 0) continue;

        // Check validity of token: optional + or -, then at least one digit
        int valid = 0;
        if (tok[0] == '+' || tok[0] == '-' || tok[0] == '*') {
            // Operator tokens must be exactly one character
            if (len == 1) {
                valid = 1;
            }
        } else if (isdigit((unsigned char)tok[0])) {
            // Must have at least one digit
            if (len > 0 && isdigit((unsigned char)tok[len-1])) {
                valid = 1;
            }
        }

        if (!valid) {
            printf("ERROR\n");
            return 0;
        }

        // Determine operator or operand
        int is_op = 0;
        int op_code = 0;
        int val = 0;

        if (tok[0] == '+' || tok[0] == '-' || tok[0] == '*') {
            // Check that the whole token is just the operator
            char expected[MAX_STACK_SIZE];
            strcpy(expected, &tok[0]);
            if (strlen(tok) == strlen(expected)) {
                is_op = 1;
                op_code = tok[0];
            }
        }

        tokens[token_count][0] = len;
        memcpy(tokens[token_count] + 1, tok, len);
        token_count++;
    }

    if (token_count == 0) {
        printf("ERROR\n");
        return 0;
    }

    // Stack
    int64 stack[MAX_STACK_SIZE];
    int top = 0;

    for (int i = 0; i < token_count; i++) {
        int len = tokens[i][0];
        char *tok_str = (char *)tokens[i] + 1;
        
        if (len == 1 && (*tok_str == '+' || *tok_str == '-' || *tok_str == '*')) {
            // Operator
            if (top < 2) {
                printf("ERROR\n");
                return 0;
            }
            int64 b = stack[top - 1];
            int64 a = stack[top - 2];
            top -= 2;
            switch (*tok_str) {
                case '+': stack[top++] = a + b; break;
                case '-': stack[top++] = a - b; break;
                case '*': stack[top++] = a * b; break;
            }
        } else {
            // Operand: parse integer
            char *endptr;
            errno = 0;
            long long val = strtoll(tok_str, &endptr, 10);
            
            // Check if entire token was consumed
            if (endptr != tok_str + len) {
                printf("ERROR\n");
                return 0;
            }

            // Check for overflow/underflow by checking errno
            if (errno == ERANGE) {
                printf("ERROR\n");
                return 0;
            }

            stack[top++] = val;
        }
    }

    if (top != 1) {
        printf("ERROR\n");
    } else {
        printf("%lld\n", stack[0]);
    }

    return 0;
}
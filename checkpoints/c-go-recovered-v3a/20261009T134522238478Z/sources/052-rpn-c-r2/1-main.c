#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 1024

int main(void) {
    char buffer[1 << 20];
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        printf("ERROR\n");
        return 0;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    if (len > 0 && buffer[len - 1] == '\r') {
        buffer[len - 1] = '\0';
        len--;
    }

    size_t pos = 0;
    while (pos < len) {
        while (pos < len && (buffer[pos] == ' ' || buffer[pos] == '\t' || buffer[pos] == '\n')) {
            pos++;
        }
        if (pos >= len) break;

        char op[64];
        size_t i = 0;
        while (pos < len && !isspace((unsigned char)buffer[pos])) {
            op[i++] = buffer[pos++];
        }
        op[i] = '\0';

        if (i == 1 && op[0] == '+') {
            // binary +, need two operands
            // will be handled by operator logic
        } else if (i == 1 && op[0] == '-') {
            // binary - or unary - in number? We handle numbers separately.
            // For now, treat as binary operator.
        } else if (i == 1 && op[0] == '*') {
            // binary *, need two operands
        }

        // Check if it's an operator
        if ((i == 1 && op[0] == '+') || (i == 1 && op[0] == '-') || (i == 1 && op[0] == '*')) {
            // This is an operator, but we need to ensure we have enough operands
            // We'll handle this in the evaluation logic
        } else if (i > 1) {
            // Check if it's a valid integer
            int negative = 0;
            if (op[0] == '+' || op[0] == '-') {
                if (op[0] == '-') negative = 1;
                pos--; // adjust position since we consumed the sign in op
            } else {
                // No sign, just digits
                // But we already incremented pos past this char, so we need to decrement
                // Actually, let's redo the parsing more carefully
            }

            // Let's re-parse this token as an integer
            long long val = 0;
            int neg = 0;
            size_t start = pos - i; // where the token started in buffer
            if (start >= len) {
                printf("ERROR\n");
                return 0;
            }

            for (size_t j = start; j < pos; j++) {
                char c = buffer[j];
                if (c == '+') {
                    // sign, but we need to check if it's the first char or after a digit
                    // Actually, in RPN, + is an operator, not part of a number
                    // So if we see + at start of token, it's an operator
                    // If we see - at start, it could be unary minus for number OR binary minus operator
                    // We need to distinguish based on context
                }
            }

            // This is getting complicated. Let's simplify:
            // Tokens are either:
            // 1. An integer (optional + or - followed by digits)
            // 2. An operator (+, -, *)
            
            // We need to check if op is a valid integer first
            int is_operator = 0;
            if (i == 1 && (op[0] == '+' || op[0] == '-' || op[0] == '*')) {
                is_operator = 1;
            } else if (i > 1) {
                // Check if it's a valid integer
                int valid_int = 1;
                if (op[0] == '+' || op[0] == '-') {
                    // Must be followed by at least one digit
                    for (size_t j = 1; j < i; j++) {
                        if (!isdigit((unsigned char)op[j])) {
                            valid_int = 0;
                            break;
                        }
                    }
                } else {
                    // Must start with a digit
                    if (!isdigit((unsigned char)op[0])) {
                        valid_int = 0;
                    } else {
                        for (size_t j = 1; j < i; j++) {
                            if (!isdigit((unsigned char)op[j])) {
                                valid_int = 0;
                                break;
                            }
                        }
                    }
                }

                if (valid_int) {
                    // Parse the integer
                    long long num = 0;
                    int sign = 1;
                    for (size_t j = 0; j < i; j++) {
                        if (op[j] == '+') {
                            // skip, no sign change needed
                        } else if (op[j] == '-') {
                            sign = -1;
                        } else {
                            num = num * 10 + (op[j] - '0');
                        }
                    }
                    num *= sign;
                    
                    // Push to stack
                    long long *stack = malloc(STACK_SIZE * sizeof(long long));
                    if (!stack) {
                        printf("ERROR\n");
                        return 0;
                    }
                    int sp = 0;
                    stack[sp++] = num;
                    
                    // Now we need to handle operators. But wait, we're parsing tokens one by one.
                    // If we see an operator, we need to check if we have enough operands.
                } else {
                    printf("ERROR\n");
                    return 0;
                }
            } else {
                // Invalid token
                printf("ERROR\n");
                return 0;
            }
        }
    }

    // Actually, let me rewrite this more cleanly
    return 0;
}
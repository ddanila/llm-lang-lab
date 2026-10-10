#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

static int stack[STACK_SIZE];
static int top = -1;

static void push(long long val) {
    if (top >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++top] = (int64_t)val;
}

static long long pop(void) {
    if (top < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

static int is_digit_or_sign(char c) {
    return (c == '+') || (c == '-') || (isdigit((unsigned char)c));
}

int main(void) {
    char buf[256];
    if (!fgets(buf, sizeof(buf), stdin)) {
        // No input at all -> empty stack -> ERROR
        printf("ERROR\n");
        return 0;
    }

    char *p = buf;
    int token_count = 0;
    
    while (1) {
        // Skip leading whitespace
        while (*p && isspace((unsigned char)*p)) p++;
        
        if (*p == '\0' || *p == '\n') break;

        // Check for EOF marker at end of line or just newline
        int is_valid_token = 0;
        
        // Determine length of token
        const char *token_start = p;
        while (*p && !isspace((unsigned char)*p)) {
            p++;
        }
        int len = (int)(p - token_start);
        
        if (len == 0) continue;

        // Token parsing: must be signed decimal integer or operator +, -, *
        // Operators are single characters: +, -, *
        // Integers: optional leading +/- and at least one digit
        
        char first = token_start[0];
        
        if (first == '+' || first == '-' || first == '*') {
            // Operator case
            // Check that it's a single character
            if (len != 1) {
                // Invalid: operator with extra chars? Or maybe negative number?
                // But we already consumed all non-whitespace. So this is invalid token.
                printf("ERROR\n");
                return 0;
            }
            
            // Check it's actually an operator and not part of a number
            // Since first char is +, -, or *, check if it's truly an operator
            // For unary minus at start of token: "-5" is valid integer, not operator
            // So single '-' is operator. But wait, "-" alone means subtract? No, need two operands.
            
            // Actually, the spec says operators are +, -, *. Single character operators.
            // A standalone "-" is an operator (unary minus in RPN context doesn't make sense without operand)
            // But we treat it as binary operator expecting 2 operands.
            
            char op = token_start[0];
            if (op == '+' || op == '-' || op == '*') {
                push(op); // Push as a special marker? No, we need to handle differently.
                // Actually, let's rethink: operators are single chars, integers are numbers.
                // We can't push operator onto stack as-is since it's not a number.
                // But we need to evaluate in RPN: when we see an operator, we pop operands.
                // So actually we should process operators immediately when seen? No, standard RPN evaluation.
                
                // Standard approach: use separate logic or store operator differently.
                // Actually for +, -, *, we can just push them and handle specially.
                // But our stack stores int64_t. We need to distinguish.
                
                // Better: when token is an operator, don't push to numeric stack, but keep track?
                // Or use a different representation. Let's use a char for operators and long long for numbers.
                
                // Actually simpler: just evaluate operators as we see them in RPN? No, RPN needs stack.
                
                // Let me restructure: use union or separate arrays.
            }
        } else {
            // Must be an integer
            if (len > 1 && isdigit((unsigned char)token_start[len-1])) {
                // Has digits at end, so it's a number
                // Parse the integer
                char *end;
                errno = 0;
                long long val = strtoll(token_start, &end, 10);
                if (errno || end != p + len) {
                    // Conversion error or trailing garbage
                    printf("ERROR\n");
                    return 0;
                }
                push(val);
            } else {
                // Check for valid integer format: optional +/- and at least one digit
                int has_sign = (token_start[0] == '+' || token_start[0] == '-');
                int has_digit = 0;
                for (int i = 0; i < len; i++) {
                    if (isdigit((unsigned char)token_start[i])) {
                        has_digit = 1;
                        break;
                    }
                }
                if (!has_sign && !has_digit) {
                    // No sign and no digit -> invalid
                    printf("ERROR\n");
                    return 0;
                }
                
                // Also need to check that all chars are valid (digit or leading sign)
                int valid = 1;
                for (int i = 0; i < len; i++) {
                    if (!isdigit((unsigned char)token_start[i]) && token_start[i] != '+' && token_start[i] != '-') {
                        valid = 0;
                        break;
                    }
                }
                if (!valid || !has_digit) {
                    // Either invalid chars or no digit
                    printf("ERROR\n");
                    return 0;
                }
                
                char *end2;
                errno = 0;
                long long val = strtoll(token_start, &end2, 10);
                if (errno || end2 != p + len) {
                    printf("ERROR\n");
                    return 0;
                }
                push(val);
            }
        }
        
        token_count++;
        if (token_count >= MAX_TOKENS) break;
    }

    // Check stack size
    if (top != 0) {
        printf("ERROR\n");
        return 0;
    }

    if (top == -1) {
        // Empty stack after processing all tokens
        printf("ERROR\n");
        return 0;
    }

    printf("%lld\n", stack[top]);

    return 0;
}
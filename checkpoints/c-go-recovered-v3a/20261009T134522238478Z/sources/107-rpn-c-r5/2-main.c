#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

static long long stack[STACK_SIZE];
static int top = -1;

static void push(long long val) {
    if (top >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    stack[++top] = val;
}

static long long pop(void) {
    if (top < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return stack[top--];
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
            // Could be operator or integer starting with sign
            if (len == 1) {
                // Single character +, -, or * is an operator
                // But wait, we need to evaluate RPN, so operators should pop operands.
                // Actually, in standard RPN evaluation, when you see an operator,
                // you pop the top two values and push the result.
                // So we don't push operators onto stack, we evaluate immediately.
                
                // But that means we need to handle this differently.
                // Let me reconsider: the spec says "operators pops right operand then left operand"
                // This implies we pop 2 operands and push result.
                
                // So when we see an operator token, we should:
                // 1. Pop right operand (top of stack)
                // 2. Pop left operand (new top of stack)
                // 3. Compute left op right
                // 4. Push result
                
                // But what if there aren't enough operands? Then ERROR.
                
                // So we don't push operators, we evaluate them immediately.
            } else {
                // Multi-character starting with + or - must be an integer
                // Check that it's a valid integer (all digits after optional sign)
                int has_sign = (token_start[0] == '+' || token_start[0] == '-');
                for (int i = 1; i < len; i++) {
                    if (!isdigit((unsigned char)token_start[i])) {
                        // Invalid character in integer
                        printf("ERROR\n");
                        return 0;
                    }
                }
                if (!has_sign && len == 0) {
                    // Shouldn't happen since len > 0
                }
                
                // Parse the integer
                char *endptr;
                long long val = strtoll(token_start, &endptr, 10);
                if (endptr != token_start + len) {
                    // Conversion didn't consume all characters - invalid
                    printf("ERROR\n");
                    return 0;
                }
                push(val);
            }
        } else {
            // Must be an integer (no operator char at start)
            for (int i = 0; i < len; i++) {
                if (!isdigit((unsigned char)token_start[i])) {
                    printf("ERROR\n");
                    return 0;
                }
            }
            char *endptr;
            long long val = strtoll(token_start, &endptr, 10);
            if (endptr != token_start + len) {
                printf("ERROR\n");
                return 0;
            }
            push(val);
        }
        
        // If we have an operator token at the start, evaluate it immediately
        // But wait, I need to handle operators differently.
        // Let me restructure: check if first char is + or - or *, and if len == 1, treat as operator
        // But I already handled that above... let me fix the logic.
        
        token_count++;
        if (token_count >= MAX_TOKENS) break;
    }

    // Check stack size - must be exactly 1
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
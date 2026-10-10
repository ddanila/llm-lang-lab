#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 200
#define STACK_SIZE 200

long long stack[STACK_SIZE];
int top = -1;

void push(long long val) {
    if (top >= STACK_SIZE - 1) return;
    stack[++top] = val;
}

long long pop(void) {
    if (top < 0) return 0;
    return stack[top--];
}

int peek(int idx) {
    if (idx < 0 || idx > top) return -1;
    return stack[idx];
}

int parse_integer(const char *s, long long *out) {
    const char *p = s;
    
    // Skip optional leading + or -
    if (*p == '+' || *p == '-') {
        p++;
    }
    
    // Check for at least one digit
    if (*p == '\0') return 0;
    
    const char *start = p;
    while (isdigit((unsigned char)*p)) {
        p++;
    }
    
    // Must have at least one digit
    if (start == p) return 0;
    
    // Parse the number
    long long val = 0;
    int neg = (*start == '-');
    
    while (start < p) {
        val = val * 10 + (*start - '0');
        start++;
    }
    
    if (neg) val = -val;
    *out = val;
    return 1;
}

int main(void) {
    char buf[1024];
    fgets(buf, sizeof(buf), stdin);
    
    // Remove trailing newline if present
    size_t len = strlen(buf);
    while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
        buf[--len] = '\0';
    }
    
    // Handle empty input
    if (len == 0) {
        printf("ERROR\n");
        return 0;
    }
    
    char *tokens[MAX_TOKENS];
    int num_tokens = 0;
    char *p = buf;
    
    // Split into tokens
    while (*p && num_tokens < MAX_TOKENS) {
        // Skip whitespace
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;
        
        const char *token_start = p;
        // Find end of token (whitespace or null)
        while (*p && !isspace((unsigned char)*p)) p++;
        
        int tok_len = p - token_start;
        tokens[num_tokens] = malloc(tok_len + 1);
        strncpy(tokens[num_tokens], token_start, tok_len);
        tokens[num_tokens][tok_len] = '\0';
        num_tokens++;
    }
    
    // Evaluate RPN
    for (int i = 0; i < num_tokens; i++) {
        const char *tok = tokens[i];
        
        if (strcmp(tok, "+") == 0) {
            long long right = pop();
            long long left = pop();
            push(left + right);
        } else if (strcmp(tok, "-") == 0) {
            long long right = pop();
            long long left = pop();
            push(left - right);
        } else if (strcmp(tok, "*") == 0) {
            long long right = pop();
            long long left = pop();
            push(left * right);
        } else {
            // Try to parse as integer
            long long val;
            if (!parse_integer(tok, &val)) {
                printf("ERROR\n");
                return 0;
            }
            push(val);
        }
    }
    
    // Check final stack size
    if (top != 0) {
        printf("ERROR\n");
        return 0;
    }
    
    // Print result
    printf("%lld\n", stack[0]);
    
    return 0;
}
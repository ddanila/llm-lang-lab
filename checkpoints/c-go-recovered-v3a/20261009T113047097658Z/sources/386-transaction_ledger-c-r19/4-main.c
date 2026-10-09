#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_STACK 10000

int stack[MAX_STACK];
int top = -1;

long balance = 0;

void push(long val) {
    if (top >= MAX_STACK - 1) return;
    stack[++top] = (int)val;
}

int pop(void) {
    if (top < 0) return 0;
    int val = stack[top];
    top--;
    return val;
}

void rollback_or_commit(int type) {
    if (top < 0) {
        printf("ERROR\n");
        return;
    }
    if (type == 1) { // ROLLBACK
        int saved = pop();
        balance = saved;
    } else { // COMMIT
        pop();
    }
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    char buf[256];
    for (int i = 0; i < N; i++) {
        if (fgets(buf, sizeof(buf), stdin) == NULL) break;
        
        // Skip leading whitespace
        char *p = buf;
        while (*p && (*p == ' ' || *p == '\t')) p++;
        
        // Check for empty line
        if (*p == '\0' || *p == '\n') continue;
        
        // Find end of command (skip trailing whitespace)
        char *end = p + strlen(p);
        while (end > p && (*(end-1) == ' ' || *(end-1) == '\t')) {
            end--;
        }
        int len = end - p;
        
        if (len >= 3 && strncmp(p, "ADD", 3) == 0) {
            long x = strtol(end, NULL, 10);
            balance += x;
        } else if (len >= 5 && strncmp(p, "BEGIN", 5) == 0) {
            push(balance);
        } else if (len >= 8 && strncmp(p, "ROLLBACK", 8) == 0) {
            rollback_or_commit(1);
        } else if (len >= 6 && strncmp(p, "COMMIT", 6) == 0) {
            rollback_or_commit(0);
        } else if (len >= 5 && strncmp(p, "PRINT", 5) == 0) {
            printf("%ld\n", balance);
        }
    }

    return 0;
}
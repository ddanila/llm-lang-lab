#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMANDS 205
#define MAX_STACK 205

int stack[MAX_STACK];
int top = -1;
long balance = 0;

void push(long val) {
    if (top >= MAX_STACK - 1) return;
    stack[++top] = (int)balance;
    balance += val;
}

void rollback_or_error(void) {
    if (top < 0) {
        fprintf(stderr, "ERROR\n");
        return;
    }
    balance = stack[top--];
}

void commit_or_error(void) {
    if (top < 0) {
        fprintf(stderr, "ERROR\n");
        return;
    }
    stack[top--];
}

int main(void) {
    char line[1024];
    int n;
    
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        
        char *p = line;
        while (*p == ' ') p++;
        int len = strlen(p);
        while (len > 0 && (p[len-1] == '\n' || p[len-1] == '\r')) {
            p[--len] = '\0';
        }
        
        if (len == 0) continue;
        
        char cmd[32];
        strncpy(cmd, p, sizeof(cmd)-1);
        cmd[sizeof(cmd)-1] = '\0';
        
        if (strncmp(cmd, "ADD", 3) == 0) {
            long x = strtol(p + 3, NULL, 10);
            balance += x;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            push(0);
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            rollback_or_error();
        } else if (strcmp(cmd, "COMMIT") == 0) {
            commit_or_error();
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }
    
    return 0;
}
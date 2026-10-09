#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 10005

int stack[MAX_STACK];
int top = -1;
int balance = 0;

void push(void) {
    if (top + 1 >= MAX_STACK) return;
    stack[++top] = balance;
}

void pop(void) {
    if (top == -1) return;
    balance = stack[top--];
}

int main(void) {
    char line[256];
    int n;
    
    if (scanf("%d", &n) != 1) return 0;
    
    for (int i = 0; i < n; i++) {
        if (!fgets(line, sizeof(line), stdin)) break;
        
        char cmd[64];
        int x;
        
        if (sscanf(line, "%63s", cmd) != 1) continue;
        
        if (strcmp(cmd, "ADD") == 0) {
            if (sscanf(line, "%*s %d", &x) == 1) {
                balance += x;
            }
        } else if (strcmp(cmd, "BEGIN") == 0) {
            push();
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top == -1) {
                printf("ERROR\n");
            } else {
                pop();
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top == -1) {
                printf("ERROR\n");
            } else {
                // discard popped value, balance unchanged
                pop();
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%d\n", balance);
        }
    }
    
    return 0;
}
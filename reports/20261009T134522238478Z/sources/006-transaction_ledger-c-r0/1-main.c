#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 205
int stack[MAX_STACK];
int top = -1;
long balance = 0;

void push(int val) {
    if (top >= MAX_STACK - 1) return;
    stack[++top] = (int)balance;
}

void pop(void) {
    if (top < 0) return;
    top--;
}

int main(void) {
    char buf[256];
    int n;
    if (scanf("%d", &n) != 1) return 0;
    
    for (int i = 0; i < n; i++) {
        if (fgets(buf, sizeof(buf), stdin) == NULL) break;
        char *cmd = strtok(buf, " \t\n\r");
        if (!cmd) continue;
        
        int x;
        if (strcmp(cmd, "ADD") == 0 && scanf("%d", &x) == 1) {
            balance += x;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            push((int)balance);
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top];
                pop();
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                pop();
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }
    
    return 0;
}
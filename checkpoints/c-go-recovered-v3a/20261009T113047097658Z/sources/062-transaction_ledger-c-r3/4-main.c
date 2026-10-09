#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 256

int stack[MAX_STACK];
int top = -1;
long balance = 0;

void push(long val) {
    if (top >= MAX_STACK - 1) return;
    stack[++top] = (int)balance;
    balance = val;
}

void pop(void) {
    if (top < 0) return;
    balance = stack[top--];
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        char buf[256];
        if (fgets(buf, sizeof(buf), stdin) == NULL) break;

        // Skip leading whitespace and find command
        char *p = buf;
        while (*p && (*p == ' ' || *p == '\t')) p++;

        if (*p == '\0') continue;

        if (strncmp(p, "ADD", 3) == 0) {
            int x = atoi(p + 4);
            balance += x;
        } else if (strncmp(p, "BEGIN", 5) == 0) {
            push(balance);
        } else if (strncmp(p, "COMMIT", 6) == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                pop();
            }
        } else if (strncmp(p, "ROLLBACK", 8) == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                pop();
            }
        } else if (strncmp(p, "PRINT", 5) == 0) {
            printf("%ld\n", balance);
        }

        // Advance past current command and any whitespace/newline
        while (*p && (*p != '\n' && *p != '\r')) p++;
    }

    return 0;
}
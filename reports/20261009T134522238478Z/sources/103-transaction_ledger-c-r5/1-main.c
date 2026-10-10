#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_STACK_SIZE 10000

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    long balance = 0;
    long stack[MAX_STACK_SIZE];
    int top = -1; // empty stack when top == -1

    for (int i = 0; i < n; i++) {
        char cmd[64];
        if (scanf("%s", cmd) != 1) break;

        if (strcmp(cmd, "ADD") == 0) {
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            top++;
            stack[top] = balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top];
                top--;
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    return 0;
}
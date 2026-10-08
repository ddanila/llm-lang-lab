#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_STACK_SIZE 10000

int stack[MAX_STACK_SIZE];
int top = -1;
long balance = 0;

void rollback_or_error(void) {
    if (top == -1) {
        printf("ERROR\n");
        return;
    }
    int val = stack[top--];
    balance = val;
}

void commit_or_error(void) {
    if (top == -1) {
        printf("ERROR\n");
        return;
    }
    stack[top--];
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    for (int i = 0; i < N; i++) {
        char cmd[32];
        scanf("%s", cmd);

        if (strcmp(cmd, "ADD") == 0) {
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            stack[++top] = (int)balance;
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
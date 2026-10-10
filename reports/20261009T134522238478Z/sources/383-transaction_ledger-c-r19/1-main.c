#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    static long stack[205];
    int top = -1; // Stack is empty when top == -1

    char cmd[32];
    int val;

    for (int i = 0; i < N; i++) {
        scanf("%s", cmd);
        if (strcmp(cmd, "ADD") == 0) {
            scanf("%d", &val);
            balance += val;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            stack[++top] = balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top--];
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
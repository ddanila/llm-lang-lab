#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int top = -1;
    int capacity = 0;

    char cmd[64];
    long val;

    for (int i = 0; i < N; i++) {
        if (scanf("%s", cmd) != 1) break;

        if (strcmp(cmd, "ADD") == 0) {
            scanf("%ld", &val);
            balance += val;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            if (top == capacity - 1) {
                capacity *= 2;
                stack = realloc(stack, capacity * sizeof(long));
                if (!stack) exit(1);
            }
            top++;
            stack[top] = balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top == -1) {
                printf("ERROR\n");
            } else {
                balance = stack[top];
                top--;
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top == -1) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
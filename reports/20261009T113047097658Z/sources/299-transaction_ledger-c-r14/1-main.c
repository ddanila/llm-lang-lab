#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int top = 0;

    for (int i = 0; i < N; i++) {
        char cmd[64];
        if (scanf("%s", cmd) != 1) break;

        if (strcmp(cmd, "ADD") == 0) {
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            stack = realloc(stack, (top + 1) * sizeof(long));
            if (!stack) break;
            stack[top++] = balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top == 0) {
                printf("ERROR\n");
            } else {
                balance = stack[--top];
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top == 0) {
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
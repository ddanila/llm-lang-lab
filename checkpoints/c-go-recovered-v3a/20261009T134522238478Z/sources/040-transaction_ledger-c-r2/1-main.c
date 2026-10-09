#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int top = 0; // number of elements in stack

    char cmd[64];
    int val;

    for (int i = 0; i < N; i++) {
        scanf("%s", cmd);
        if (strcmp(cmd, "ADD") == 0) {
            scanf("%d", &val);
            balance += val;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            stack = realloc(stack, ++top * sizeof(long));
            stack[top - 1] = balance;
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
                long saved = stack[--top];
                // discard saved value, balance remains unchanged
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
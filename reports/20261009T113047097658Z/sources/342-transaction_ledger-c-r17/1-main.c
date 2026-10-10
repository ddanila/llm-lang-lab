#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int top = 0;  // number of elements in stack (top is index of next free slot)

    for (int i = 0; i < N; i++) {
        char cmd[16];
        if (!scanf("%s", cmd)) break;

        if (strcmp(cmd, "ADD") == 0) {
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            stack = realloc(stack, ++top * sizeof(long));
            stack[top - 1] = balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top == 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top - 1];
                top--;
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
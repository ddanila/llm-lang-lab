#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    int capacity = 256;
    long *stack = malloc(capacity * sizeof(long));
    int top = 0; // number of elements in stack

    char cmd[32];
    int x;

    for (int i = 0; i < N; i++) {
        scanf("%s", cmd);
        if (strcmp(cmd, "ADD") == 0) {
            scanf("%d", &x);
            balance += x;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            if (top < capacity - 1) {
                stack[top++] = balance;
            }
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top > 0) {
                balance = stack[--top];
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top > 0) {
                top--;
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
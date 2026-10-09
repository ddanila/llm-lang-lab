#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    int capacity = N + 2;
    long *stack = malloc(capacity * sizeof(long));
    if (!stack) return 1;
    int top = -1; // empty stack

    for (int i = 0; i < N; i++) {
        char cmd[64];
        scanf("%s", cmd);
        if (cmd[0] == 'A') { // ADD x
            long x;
            scanf("%ld", &x);
            balance += x;
        } else if (cmd[0] == 'B') { // BEGIN
            top++;
            stack[top] = balance;
        } else if (cmd[0] == 'R') { // ROLLBACK
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top];
                top--;
            }
        } else if (cmd[0] == 'C') { // COMMIT
            if (top < 0) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (cmd[0] == 'P') { // PRINT
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int top = -1;

    for (int i = 0; i < N; ++i) {
        char cmd[64];
        if (scanf("%63s", cmd) != 1) break;

        if (cmd[0] == 'A') {
            // ADD x
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (cmd[0] == 'B') {
            // BEGIN
            top++;
            stack = realloc(stack, (top + 1) * sizeof(long));
            if (!stack) break;
            stack[top] = balance;
        } else if (cmd[0] == 'R') {
            // ROLLBACK
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top];
                top--;
            }
        } else if (cmd[0] == 'C') {
            // COMMIT
            if (top < 0) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (cmd[0] == 'P') {
            // PRINT
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
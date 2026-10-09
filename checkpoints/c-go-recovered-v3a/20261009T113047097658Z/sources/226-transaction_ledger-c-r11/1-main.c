#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int stack_size = 0;
    int capacity = 0;

    for (int i = 0; i < N; i++) {
        char cmd[32];
        if (scanf("%31s", cmd) != 1) break;

        if (cmd[0] == 'A') {
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (cmd[0] == 'B') {
            // BEGIN
            if (capacity <= stack_size) {
                capacity = stack_size == 0 ? 8 : stack_size * 2;
                stack = realloc(stack, capacity * sizeof(long));
                if (!stack) return 1;
            }
            stack[stack_size++] = balance;
        } else if (cmd[0] == 'R') {
            // ROLLBACK
            if (stack_size == 0) {
                printf("ERROR\n");
            } else {
                balance = stack[--stack_size];
            }
        } else if (cmd[0] == 'C') {
            // COMMIT
            if (stack_size == 0) {
                printf("ERROR\n");
            } else {
                stack[--stack_size]; // discard saved value
            }
        } else if (cmd[0] == 'P') {
            // PRINT
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int top = 0;

    for (int i = 0; i < N; i++) {
        char cmd[32];
        if (scanf("%s", cmd) != 1) break;

        if (cmd[0] == 'A' && cmd[1] == 'D' && cmd[2] == 'D') {
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (cmd[0] == 'B' && cmd[1] == 'E' && cmd[2] == 'G' && cmd[3] == 'I' && cmd[4] == 'N') {
            stack = realloc(stack, ++top * sizeof(long));
            stack[top - 1] = balance;
        } else if (cmd[0] == 'R' && cmd[1] == 'O' && cmd[2] == 'L' && cmd[3] == 'L' && cmd[4] == 'B' && cmd[5] == 'A' && cmd[6] == 'C' && cmd[7] == 'K') {
            if (top > 0) {
                balance = stack[top - 1];
                top--;
            } else {
                printf("ERROR\n");
            }
        } else if (cmd[0] == 'C' && cmd[1] == 'O' && cmd[2] == 'M' && cmd[3] == 'M' && cmd[4] == 'I' && cmd[5] == 'T') {
            if (top > 0) {
                top--;
            } else {
                printf("ERROR\n");
            }
        } else if (cmd[0] == 'P' && cmd[1] == 'R' && cmd[2] == 'I' && cmd[3] == 'N' && cmd[4] == 'T') {
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
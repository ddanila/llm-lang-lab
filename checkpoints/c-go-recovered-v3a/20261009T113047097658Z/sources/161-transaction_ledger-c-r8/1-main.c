#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    int capacity = 205;
    long *stack = malloc(capacity * sizeof(long));
    int top = -1;

    for (int i = 0; i < N; i++) {
        char cmd[64];
        scanf("%s", cmd);
        if (cmd[0] == 'A') {
            long x;
            scanf("%ld", &x);
            balance += x;
        } else if (cmd[0] == 'B') {
            stack[++top] = balance;
        } else if (cmd[0] == 'R') {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top--];
            }
        } else if (cmd[0] == 'C') {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (cmd[0] == 'P') {
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
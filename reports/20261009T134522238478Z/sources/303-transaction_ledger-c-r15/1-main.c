#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_STACK 205

int stack[MAX_STACK];
int top = -1;
int balance = 0;

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    for (int i = 0; i < N; i++) {
        char cmd[64];
        int x;
        scanf("%s", cmd);
        if (cmd[0] == 'A') { // ADD
            scanf("%d", &x);
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
            printf("%d\n", balance);
        }
    }

    return 0;
}
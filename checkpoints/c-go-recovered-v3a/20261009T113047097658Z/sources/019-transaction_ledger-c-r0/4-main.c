#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 205

int stack[MAX_STACK];
int top = -1;
long balance = 0;

void push(void) {
    if (top < MAX_STACK - 1) {
        stack[++top] = (int)balance;
    }
}

void pop(int *out) {
    if (top >= 0) {
        *out = stack[top--];
    } else {
        *out = -1;
    }
}

int main(void) {
    int N;
    char cmd[32];
    long x;

    if (scanf("%d", &N) != 1) {
        return 0;
    }

    for (int i = 0; i < N; i++) {
        if (scanf("%31s", cmd) != 1) break;

        if (cmd[0] == 'A') { /* ADD */
            scanf("%ld", &x);
            balance += x;
        } else if (cmd[0] == 'B') { /* BEGIN */
            push();
        } else if (cmd[0] == 'R') { /* ROLLBACK or COMMIT */
            char rest[32];
            scanf("%s", rest);
            if (rest[0] == 'O') { /* ROLLBACK */
                int saved;
                pop(&saved);
                if (saved != -1) {
                    balance = saved;
                }
            } else if (rest[0] == 'M') { /* COMMIT */
                int saved;
                pop(&saved);
                if (saved != -1) {
                    // discard saved, don't restore
                } else {
                    printf("ERROR\n");
                }
            }
        } else if (cmd[0] == 'P') { /* PRINT */
            printf("%ld\n", balance);
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = malloc(205 * sizeof(long));
    int top = 0; // number of elements in stack

    for (int i = 0; i < N; i++) {
        char buf[64];
        scanf("%s", buf);
        
        if (buf[0] == 'A') { // ADD
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (buf[0] == 'B') { // BEGIN
            stack[top++] = balance;
        } else if (buf[0] == 'R') { // ROLLBACK
            if (top == 0) {
                printf("ERROR\n");
            } else {
                balance = stack[--top];
            }
        } else if (buf[0] == 'C') { // COMMIT
            if (top == 0) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (buf[0] == 'P') { // PRINT
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
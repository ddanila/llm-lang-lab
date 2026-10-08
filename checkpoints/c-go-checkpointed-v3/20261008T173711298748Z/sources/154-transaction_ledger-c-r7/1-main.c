#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = malloc(205 * sizeof(long));
    if (!stack) return 0;
    int stack_top = -1; // empty

    char buf[64];
    for (int i = 0; i < N; ++i) {
        if (scanf("%s", buf) != 1) break;
        if (strcmp(buf, "ADD") == 0) {
            int x; scanf("%d", &x);
            balance += x;
        } else if (strcmp(buf, "BEGIN") == 0) {
            stack[++stack_top] = balance;
        } else if (strcmp(buf, "ROLLBACK") == 0) {
            if (stack_top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[stack_top--];
            }
        } else if (strcmp(buf, "COMMIT") == 0) {
            if (stack_top < 0) {
                printf("ERROR\n");
            } else {
                stack_top--;
            }
        } else if (strcmp(buf, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
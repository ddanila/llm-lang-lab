#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    int *stack = NULL;
    int top = -1;

    for (int i = 0; i < N; i++) {
        char cmd[32];
        int val;
        
        // Read command and optional argument
        if (scanf("%s", cmd) != 1) break;
        
        if (strcmp(cmd, "ADD") == 0) {
            scanf("%d", &val);
            balance += val;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            top++;
            stack = realloc(stack, (top + 1) * sizeof(int));
            if (!stack) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            stack[top] = (int)balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top];
                top--;
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
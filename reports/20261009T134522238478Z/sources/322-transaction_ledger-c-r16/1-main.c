#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    int capacity = N + 50;
    long *stack = malloc(capacity * sizeof(long));
    int top = -1;

    char buf[256];
    while (N > 0) {
        if (!fgets(buf, sizeof(buf), stdin)) break;
        
        char cmd[32] = "";
        char arg[128] = "";
        int len = sscanf(buf, "%s", cmd);
        if (len < 1) continue;

        if (strcmp(cmd, "ADD") == 0) {
            int x;
            if (sscanf(buf, "%*s %d", &x) == 1) {
                balance += x;
                N--;
            }
        } else if (strcmp(cmd, "BEGIN") == 0) {
            top++;
            if (top >= capacity - 1) {
                int new_cap = capacity * 2;
                long *new_stack = realloc(stack, new_cap * sizeof(long));
                if (new_stack) stack = new_stack;
                else break;
                capacity = new_cap;
            }
            stack[top] = balance;
            N--;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top >= 0) {
                balance = stack[top];
                top--;
                N--;
            } else {
                printf("ERROR\n");
                N--;
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top >= 0) {
                top--;
                N--;
            } else {
                printf("ERROR\n");
                N--;
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
            N--;
        }
    }

    free(stack);
    return 0;
}
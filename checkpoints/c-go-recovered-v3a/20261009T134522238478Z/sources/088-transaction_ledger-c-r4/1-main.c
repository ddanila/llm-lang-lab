#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int top = -1; // stack is empty when top == -1

    char buf[256];
    while (n > 0 && fgets(buf, sizeof(buf), stdin) != NULL) {
        // Trim newline
        size_t len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';

        char *cmd = strtok(buf, " \t\n");
        if (!cmd) continue;

        int val = 0;
        int x = atoi(cmd); // command argument

        if (strcmp(cmd, "ADD") == 0) {
            balance += x;
            n--;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            top++;
            stack = realloc(stack, (top + 1) * sizeof(long));
            if (!stack) { free(stack); return 1; }
            stack[top] = balance;
            n--;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top];
                top--;
            }
            n--;
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                top--; // discard the saved balance without restoring it
            }
            n--;
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
            n--;
        }
    }

    free(stack);
    return 0;
}
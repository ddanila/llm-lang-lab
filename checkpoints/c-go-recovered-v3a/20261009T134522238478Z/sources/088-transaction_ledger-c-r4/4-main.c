#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    // Consume any remaining characters after n (including newline)
    char c;
    while ((c = getchar()) != '\n' && c != EOF);

    long balance = 0;
    long *stack = NULL;
    int top = -1;

    char buf[256];
    for (int i = 0; i < n; i++) {
        if (!fgets(buf, sizeof(buf), stdin)) break;
        
        size_t len = strlen(buf);
        if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';

        char *cmd = strtok(buf, " \t\n");
        if (!cmd) continue;

        int x = atoi(cmd);

        if (strcmp(cmd, "ADD") == 0) {
            // Need to read the argument for ADD
            char *arg = strtok(NULL, " \t\n");
            if (arg) balance += atoi(arg);
        } else if (strcmp(cmd, "BEGIN") == 0) {
            top++;
            stack = realloc(stack, (top + 1) * sizeof(long));
            if (!stack) { free(stack); return 1; }
            stack[top] = balance;
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
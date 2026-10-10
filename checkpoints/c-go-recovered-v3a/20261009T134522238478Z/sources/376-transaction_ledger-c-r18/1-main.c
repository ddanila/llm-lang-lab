#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long *stack = NULL;
    int top = 0;  // stack[top] is the next free slot

    char buf[1024];
    char cmd[64];
    int x;

    for (int i = 0; i < N; i++) {
        if (!fgets(buf, sizeof(buf), stdin)) break;

        // Remove newline
        size_t len = strlen(buf);
        while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
            buf[--len] = '\0';
        }

        if (len == 0) continue;

        char *p = buf;
        int nread = sscanf(p, "%63s", cmd);
        if (nread != 1) continue;

        if (strcmp(cmd, "ADD") == 0) {
            if (sscanf(buf, "%*[^ ] %d", &x) == 1) {
                balance += x;
            }
        } else if (strcmp(cmd, "BEGIN") == 0) {
            stack = realloc(stack, (top + 2) * sizeof(long));
            if (!stack) break;
            stack[top++] = balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top > 0) {
                balance = stack[--top];
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top > 0) {
                top--;
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    free(stack);
    return 0;
}
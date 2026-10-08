#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 205

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long stack[MAX_STACK];
    int top = -1; // empty stack

    char buf[1024];
    for (int i = 0; i < N; i++) {
        if (fgets(buf, sizeof(buf), stdin) == NULL) break;
        
        // Remove newline
        size_t len = strlen(buf);
        while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
            buf[--len] = '\0';
        }

        if (len == 0) continue;

        // Find command start
        char *cmd = buf;
        while (*cmd && (*cmd <= ' ')) cmd++;

        if (strcmp(cmd, "ADD") == 0) {
            int x;
            if (sscanf(buf, "%d", &x) == 1) {
                balance += x;
            }
        } else if (strcmp(cmd, "BEGIN") == 0) {
            stack[++top] = balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top >= 0) {
                balance = stack[top--];
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top >= 0) {
                top--; // discard saved balance, don't restore
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    return 0;
}
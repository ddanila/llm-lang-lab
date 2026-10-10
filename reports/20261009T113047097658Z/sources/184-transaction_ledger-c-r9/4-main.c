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

        // Find command start and value end
        char *cmd = buf;
        while (*cmd && (*cmd <= ' ')) cmd++;

        if (strncmp(cmd, "ADD", 3) == 0) {
            // Skip "ADD"
            char *val_start = cmd + 3;
            while (*val_start && (*val_start <= ' ')) val_start++;
            
            long x = 0;
            for (; *val_start && (*val_start >= '0' && *val_start <= '9'); val_start++) {
                x = x * 10 + (*val_start - '0');
            }
            balance += x;
        } else if (strncmp(cmd, "BEGIN", 5) == 0) {
            stack[++top] = balance;
        } else if (strncmp(cmd, "ROLLBACK", 8) == 0) {
            if (top >= 0) {
                balance = stack[top--];
            } else {
                printf("ERROR\n");
            }
        } else if (strncmp(cmd, "COMMIT", 6) == 0) {
            if (top >= 0) {
                top--; // discard saved balance, don't restore
            } else {
                printf("ERROR\n");
            }
        } else if (strncmp(cmd, "PRINT", 5) == 0) {
            printf("%ld\n", balance);
        }
    }

    return 0;
}
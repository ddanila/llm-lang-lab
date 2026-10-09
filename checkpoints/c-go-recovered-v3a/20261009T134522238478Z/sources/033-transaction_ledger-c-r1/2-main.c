#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_STACK 200

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long balance = 0;
    long saved[MAX_STACK];
    int top = 0; // points to next free slot, so saved[0..top-1] are valid

    char buf[256];
    while (n-- > 0 && fgets(buf, sizeof(buf), stdin)) {
        char *p = buf;
        while (*p == ' ') p++;
        if (*p == '\0') continue;

        int len = strlen(p);
        int i = 0;
        for (; i < len && p[i] <= ' '; i++) {}
        if (len - i < 2) continue;

        char cmd[32];
        strncpy(cmd, p, sizeof(cmd));
        cmd[sizeof(cmd)-1] = '\0';
        int ci = 0;
        while (ci < (int)sizeof(cmd) && cmd[ci] != ' ' && cmd[ci] != '\n' && cmd[ci] != '\r') {
            cmd[ci++] = p[i++];
        }
        cmd[ci] = '\0';

        int val = 0;
        if (i < len) {
            char *num = p + i;
            while (*num == ' ') num++;
            // parse integer
            val = 0;
            for (; *num != ' ' && *num != '\n' && *num != '\r'; num++) {
                if (*num < '0' || *num > '9') break;
                val = val * 10 + (*num - '0');
            }
        }

        if (strcmp(cmd, "ADD") == 0) {
            balance += val;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            saved[top++] = balance;
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top > 0) {
                balance = saved[--top];
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top > 0) {
                top--; // discard without restoring
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_STACK 205

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long balance = 0;
    long stack[MAX_STACK];
    int top = 0; // number of elements in stack

    char buf[65536];
    size_t len = 0;
    int c;
    
    while ((c = getchar()) != EOF && len < sizeof(buf)) {
        if (c == '\n' || c == ' ') {
            if (len > 0) {
                buf[len] = '\0';
                size_t start = 0, end = len - 1;
                while (start <= end && (buf[start] == ' ' || buf[start] == '\n')) start++;
                while (end >= start && (buf[end] == ' ' || buf[end] == '\n')) end--;
                if (start <= end) {
                    char cmd[32];
                    int i = 0;
                    for (size_t j = start; j <= end && i < 31; j++) {
                        if (buf[j] >= 'A' && buf[j] <= 'Z') {
                            cmd[i++] = buf[j];
                        } else if (buf[j] == ' ') {
                            break;
                        }
                    }
                    cmd[i] = '\0';
                    
                    // Skip past the command name to find optional argument
                    size_t arg_start = end + 1;
                    while (arg_start < len && buf[arg_start] == ' ') arg_start++;
                    
                    if (strcmp(cmd, "ADD") == 0) {
                        long val = 0;
                        for (size_t j = arg_start; j < len && buf[j] != ' ' && buf[j] != '\n'; j++) {
                            if (buf[j] >= '0' && buf[j] <= '9') {
                                val = val * 10 + (buf[j] - '0');
                            }
                        }
                        balance += val;
                    } else if (strcmp(cmd, "BEGIN") == 0) {
                        stack[top++] = balance;
                    } else if (strcmp(cmd, "ROLLBACK") == 0) {
                        if (top > 0) {
                            balance = stack[--top];
                        } else {
                            printf("ERROR\n");
                        }
                    } else if (strcmp(cmd, "COMMIT") == 0) {
                        if (top > 0) {
                            top--; // discard saved balance without restoring
                        } else {
                            printf("ERROR\n");
                        }
                    } else if (strcmp(cmd, "PRINT") == 0) {
                        printf("%ld\n", balance);
                    }
                }
            }
            len = 0;
        } else {
            buf[len++] = c;
        }
    }

    return 0;
}
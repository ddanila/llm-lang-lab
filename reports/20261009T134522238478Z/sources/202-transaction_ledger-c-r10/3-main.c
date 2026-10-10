#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 205

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long balance = 0;
    long stack[MAX_STACK];
    int top = 0; // number of elements in stack

    char cmd[32];
    char arg[32];
    
    for (int i = 0; i < n; i++) {
        if (scanf("%31s%31s", cmd, arg) == 2) {
            if (strcmp(cmd, "ADD") == 0) {
                balance += atol(arg);
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
        } else if (scanf("%31s", cmd) == 1) {
            // No argument - BEGIN, ROLLBACK, COMMIT, PRINT have no args
            if (strcmp(cmd, "BEGIN") == 0) {
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

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_STACK 10000

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    int stack[MAX_STACK];
    int top = -1;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove newline
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';

        char cmd[32];
        int arg;
        
        if (sscanf(buffer, "%s %d", cmd, &arg) == 2) {
            if (strcmp(cmd, "ADD") == 0) {
                balance += arg;
            } else if (strcmp(cmd, "BEGIN") == 0) {
                top++;
                stack[top] = (int)balance;
            } else if (strcmp(cmd, "ROLLBACK") == 0) {
                if (top >= 0) {
                    balance = stack[top];
                    top--;
                } else {
                    printf("ERROR\n");
                }
            } else if (strcmp(cmd, "COMMIT") == 0) {
                if (top >= 0) {
                    top--;
                } else {
                    printf("ERROR\n");
                }
            } else if (strcmp(cmd, "PRINT") == 0) {
                printf("%ld\n", balance);
            }
        } else if (sscanf(buffer, "%s", cmd) == 1) {
            // No argument command - only PRINT has no arg in this spec but it prints
            if (strcmp(cmd, "PRINT") == 0) {
                printf("%ld\n", balance);
            }
        }
    }

    return 0;
}
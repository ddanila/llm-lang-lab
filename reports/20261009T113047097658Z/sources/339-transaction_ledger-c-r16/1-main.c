#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    long balance = 0;
    char *stack[200];
    int top = -1;
    
    for (int i = 0; i < N; i++) {
        char cmd[32];
        if (!scanf("%s", cmd)) break;
        
        if (strcmp(cmd, "ADD") == 0) {
            int x;
            scanf("%d", &x);
            balance += x;
        } else if (strcmp(cmd, "BEGIN") == 0) {
            stack[++top] = malloc(8);
            if (stack[top]) {
                long val = balance;
                memcpy(stack[top], &val, 8);
            }
        } else if (strcmp(cmd, "ROLLBACK") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                long saved;
                memcpy(&saved, stack[top], 8);
                balance = saved;
                free(stack[top]);
                top--;
            }
        } else if (strcmp(cmd, "COMMIT") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                free(stack[top]);
                top--;
            }
        } else if (strcmp(cmd, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }
    
    return 0;
}
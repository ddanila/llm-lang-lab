#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_STACK 10000

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long balance = 0;
    long stack[MAX_STACK];
    int top = -1; // empty stack

    char buf[256];
    while (N > 0) {
        int consumed = scanf("%s", buf);
        if (consumed != 1) break;

        N--;
        if (strcmp(buf, "ADD") == 0) {
            int x;
            if (scanf("%d", &x) == 1) {
                balance += x;
            }
        } else if (strcmp(buf, "BEGIN") == 0) {
            top++;
            stack[top] = balance;
        } else if (strcmp(buf, "ROLLBACK") == 0) {
            if (top >= 0) {
                balance = stack[top];
                top--;
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(buf, "COMMIT") == 0) {
            if (top >= 0) {
                top--;
            } else {
                printf("ERROR\n");
            }
        } else if (strcmp(buf, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
    }

    return 0;
}
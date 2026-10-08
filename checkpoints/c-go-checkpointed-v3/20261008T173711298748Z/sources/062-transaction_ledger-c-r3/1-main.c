#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 256

int stack[MAX_STACK];
int top = -1;
long balance = 0;

void push(long val) {
    if (top >= MAX_STACK - 1) return;
    stack[++top] = (int)balance;
    balance = val;
}

void pop(void) {
    if (top < 0) return;
    balance = stack[top--];
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        char buf[64];
        if (fgets(buf, sizeof(buf), stdin) == NULL) break;

        int len = 0;
        while (len < (int)sizeof(buf)-1 && buf[len] != '\n' && buf[len] != '\r') {
            len++;
        }
        buf[len] = '\0';

        char *p = buf;
        while (*p == ' ') p++;

        if (*p == '\0') continue;

        if (p[4] == 'D' && p[0] == 'A') { // ADD
            int x = 0;
            for (char *q = p + 5; *q != '\0'; q++) {
                if (*q >= '0' && *q <= '9') x = x * 10 + (*q - '0');
            }
            balance += x;
        } else if (p[4] == 'G' && p[0] == 'B') { // BEGIN
            push(balance);
        } else if (p[5] == 'M' && p[0] == 'C') { // COMMIT
            if (top < 0) {
                printf("ERROR\n");
            } else {
                pop();
            }
        } else if (p[6] == 'L' && p[0] == 'R') { // ROLLBACK
            if (top < 0) {
                printf("ERROR\n");
            } else {
                pop();
            }
        } else if (p[4] == 'N' && p[0] == 'P') { // PRINT
            printf("%ld\n", balance);
        }

        while (*p != '\0' && *p != '\n' && *p != '\r') p++;
    }

    return 0;
}
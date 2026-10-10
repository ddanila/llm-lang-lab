#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200
#define MAX_STACK 10000

int stack[MAX_STACK];
int top = -1;

long balance = 0;

void push(int val) {
    if (top >= MAX_STACK - 1) return;
    stack[++top] = val;
}

int pop(void) {
    if (top < 0) return 0;
    int val = stack[top];
    top--;
    return val;
}

void rollback_or_commit(int type) {
    if (top < 0) {
        printf("ERROR\n");
        return;
    }
    if (type == 1) { // ROLLBACK
        int saved = pop();
        balance = saved;
    } else { // COMMIT
        pop();
    }
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    char buf[256];
    for (int i = 0; i < N; i++) {
        if (fgets(buf, sizeof(buf), stdin) == NULL) break;
        char *p = buf;
        while (*p == ' ') p++;
        if (*p == '\0' || *p == '\n') continue;

        int len = strlen(p);
        for (int k = 0; k < len && (p[k] == ' ' || p[k] == '\n' || p[k] == '\r'); k++) {
            p++;
        }
        if (*p == '\0') continue;

        if (strncmp(p, "ADD", 3) == 0) {
            p += 3;
            while (*p == ' ') p++;
            long x = strtol(p, NULL, 10);
            balance += x;
        } else if (strncmp(p, "BEGIN", 5) == 0) {
            push((int)balance);
        } else if (strncmp(p, "ROLLBACK", 8) == 0) {
            rollback_or_commit(1);
        } else if (strncmp(p, "COMMIT", 6) == 0) {
            rollback_or_commit(0);
        } else if (strncmp(p, "PRINT", 5) == 0) {
            printf("%ld\n", balance);
        }
    }

    return 0;
}
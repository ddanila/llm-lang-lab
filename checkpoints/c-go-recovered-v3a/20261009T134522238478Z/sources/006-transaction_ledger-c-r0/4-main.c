#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 205
int stack[MAX_STACK];
int top = -1;
long balance = 0;

void push(void) {
    if (top >= MAX_STACK - 1) return;
    stack[++top] = (int)balance;
}

void pop(void) {
    if (top < 0) return;
    top--;
}

int main(void) {
    char buf[256];
    int n;
    
    // Read n, consume any leftover newline
    if (scanf("%d", &n) != 1) return 0;
    while (getchar() != '\n' && !feof(stdin));
    
    for (int i = 0; i < n; i++) {
        if (fgets(buf, sizeof(buf), stdin) == NULL) break;
        
        char *p = buf;
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') p++;
        if (*p == '\0') continue;
        
        int x;
        if (strncmp(p, "ADD", 3) == 0 && sscanf(p + 4, "%d", &x) == 1) {
            balance += x;
        } else if (strncmp(p, "BEGIN", 5) == 0) {
            push();
        } else if (strncmp(p, "ROLLBACK", 8) == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = stack[top];
                pop();
            }
        } else if (strncmp(p, "COMMIT", 6) == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                pop();
            }
        } else if (strncmp(p, "PRINT", 5) == 0) {
            printf("%ld\n", balance);
        }
    }
    
    return 0;
}
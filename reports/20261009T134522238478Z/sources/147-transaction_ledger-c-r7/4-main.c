#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 205

int stack[MAX_STACK];
int top = -1;
long balance = 0;

void push(long val) {
    if (top >= MAX_STACK - 1) return;
    stack[++top] = (int)val;
}

long pop(void) {
    if (top < 0) return 0;
    return stack[top--];
}

int main(void) {
    char buf[256];
    int n, cmd, val;
    
    // Read N
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;
    sscanf(buf, "%d", &n);
    
    for (int i = 0; i < n; ) {
        // Read command and optional value
        char cmd_str[32];
        int read = fread(cmd_str, 1, sizeof(cmd_str)-1, stdin);
        if (read == 0) break;
        
        cmd_str[read] = '\0';
        
        if (cmd_str[0] == 'A') {  // ADD
            int val = 0;
            sscanf(cmd_str, "%d", &val);
            balance += val;
        } else if (cmd_str[0] == 'B') {  // BEGIN
            push(balance);
        } else if (cmd_str[0] == 'R') {  // ROLLBACK
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = pop();
            }
        } else if (cmd_str[0] == 'C') {  // COMMIT
            if (top < 0) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (cmd_str[0] == 'P') {  // PRINT
            printf("%ld\n", balance);
        }
        
        i++;
    }
    
    return 0;
}
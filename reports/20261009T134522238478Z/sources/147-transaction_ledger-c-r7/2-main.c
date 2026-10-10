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
    
    // Read N
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;
    int n = atoi(buf);
    
    for (int i = 0; i < n; ) {
        // Read next non-whitespace character to get command
        int c = getchar();
        while (c != EOF && (c == ' ' || c == '\t' || c == '\n' || c == '\r')) {
            c = getchar();
        }
        
        if (c == EOF) break;
        
        // Read full command token
        char cmd[32];
        int j = 0;
        while (j < sizeof(cmd) - 1 && c != EOF && c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            cmd[j++] = (char)c;
            c = getchar();
        }
        cmd[j] = '\0';
        
        // Read rest of line/number if needed
        while ((c = getchar()) != EOF && c != '\n' && c != '\r') {}
        
        if (cmd[0] == 'A') {  // ADD
            int val = 0;
            // Skip whitespace
            while ((c = getchar()) != EOF && (c == ' ' || c == '\t')) {}
            if (c != EOF) sscanf(&buf[i], "%d", &val);
            balance += val;
        } else if (cmd[0] == 'B') {  // BEGIN
            push(balance);
        } else if (cmd[0] == 'R') {  // ROLLBACK
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = pop();
            }
        } else if (cmd[0] == 'C') {  // COMMIT
            if (top < 0) {
                printf("ERROR\n");
            } else {
                top--;
            }
        } else if (cmd[0] == 'P') {  // PRINT
            printf("%ld\n", balance);
        }
        
        i++;
    }
    
    return 0;
}
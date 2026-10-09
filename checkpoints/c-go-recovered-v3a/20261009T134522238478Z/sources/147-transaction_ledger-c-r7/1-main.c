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
    int n, x;
    int cmd_len;
    
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;
    
    // Read N
    sscanf(buf, "%d", &n);
    
    for (int i = 0; i < n; ) {
        // Get next command token
        int c = getchar();
        if (c == EOF || c == '\n' || c == '\r') continue;
        
        // Skip whitespace
        while (c == ' ' || c == '\t') c = getchar();
        if (c == EOF) break;
        
        char cmd[32] = {0};
        int j = 0;
        while (j < sizeof(cmd) - 1 && (c >= 'a' && c <= 'z')) {
            cmd[j++] = (char)c;
            c = getchar();
        }
        cmd[j] = '\0';
        
        // Check if uppercase command
        char upper[32];
        for (int k = 0; k < j; k++) upper[k] = (char)(cmd[k] + 'A' - 'a');
        upper[j] = '\0';
        
        // Read rest of line
        while ((c = getchar()) != EOF && c != '\n' && c != '\r') {}
        
        if (strcmp(upper, "ADD") == 0) {
            int val = 0;
            // Skip whitespace
            while ((c = getchar()) != EOF && (c == ' ' || c == '\t')) {}
            if (c != EOF) sscanf(&cmd[3], "%d", &val);
            balance += val;
        } else if (strcmp(upper, "BEGIN") == 0) {
            push(balance);
        } else if (strcmp(upper, "ROLLBACK") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                balance = pop();
            }
        } else if (strcmp(upper, "COMMIT") == 0) {
            if (top < 0) {
                printf("ERROR\n");
            } else {
                // Pop without restoring
                top--;
            }
        } else if (strcmp(upper, "PRINT") == 0) {
            printf("%ld\n", balance);
        }
        
        i++;
    }
    
    return 0;
}
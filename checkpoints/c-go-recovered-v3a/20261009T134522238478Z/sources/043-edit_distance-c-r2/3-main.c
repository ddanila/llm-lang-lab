#include <stdio.h>
#include <string.h>

int main(void) {
    char line1[82], line2[82];
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;
    
    // Remove trailing newline if present
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    if (len1 > 0 && line1[len1-1] == '\n') { line1[--len1] = '\0'; }
    if (len2 > 0 && line2[len2-1] == '\n') { line2[--len2] = '\0'; }
    
    int dp[82][82];
    
    for (int i = 0; i <= len1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= len2; j++) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if ((char)line1[i-1] == line2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                int sub = dp[i-1][j-1] + 1;
                int del = dp[i-1][j] + 1;
                int ins = dp[i][j-1] + 1;
                if (sub <= del && sub <= ins)
                    dp[i][j] = sub;
                else if (del < ins)
                    dp[i][j] = del;
                else
                    dp[i][j] = ins;
            }
        }
    }
    
    printf("%d\n", dp[len1][len2]);
    return 0;
}
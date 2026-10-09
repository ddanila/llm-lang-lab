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
    
    int dp[len1 + 1][len2 + 1];
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) dp[i][j] = j;
            else if (j == 0) dp[i][j] = i;
            else if (line1[i-1] == line2[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + (dp[i-1][j] < dp[i][j-1] ? 
                                 (dp[i-1][j] < dp[i-1][j-1] ? dp[i-1][j] : dp[i-1][j-1]) :
                                 dp[i][j-1]);
        }
    }
    
    printf("%d\n", dp[len1][len2]);
    return 0;
}
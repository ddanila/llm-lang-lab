#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char line1[81], line2[81];
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;
    
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    
    // Remove newline characters if present
    if (len1 > 0 && line1[len1-1] == '\n') {
        line1[len1-1] = '\0';
        len1--;
    }
    if (len2 > 0 && line2[len2-1] == '\n') {
        line2[len2-1] = '\0';
        len2--;
    }
    
    // Ensure len1 <= len2 for optimization
    int n, m;
    char *s1, *s2;
    if (len1 > len2) {
        n = (int)len2;
        m = (int)len1;
        s1 = line2;
        s2 = line1;
    } else {
        n = (int)len1;
        m = (int)len2;
        s1 = line1;
        s2 = line2;
    }
    
    // dp[i][j] = edit distance between s1[0..i-1] and s2[0..j-1]
    int dp[m + 1][n + 1];
    
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;
            dp[i][j] = dp[i-1][j-1] + cost;
            if (dp[i-1][j] < dp[i][j]) {
                dp[i][j] = dp[i-1][j] + 1;
            }
            if (dp[i][j-1] < dp[i][j]) {
                dp[i][j] = dp[i][j-1] + 1;
            }
        }
    }
    
    printf("%d\n", dp[m][n]);
    
    return 0;
}
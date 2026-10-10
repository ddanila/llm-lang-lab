#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int main(void) {
    char line1[82] = {0};
    char line2[82] = {0};
    
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;
    
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    
    // Remove newline characters if present
    for (size_t i = 0; i < len1 && line1[i] != '\n'; i++);
    for (size_t i = 0; i < len2 && line2[i] != '\n'; i++);
    
    int n = (int)len1;
    int m = (int)len2;
    
    // dp[i][j] = edit distance between first i chars of s1 and first j chars of s2
    int dp[82][82];
    
    for (int i = 0; i <= n; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cost = (line1[i-1] == line2[j-1]) ? 0 : 1;
            dp[i][j] = min(dp[i-1][j] + 1,      // deletion
                           dp[i][j-1] + 1,      // insertion
                           dp[i-1][j-1] + cost); // substitution
        }
    }
    
    printf("%d\n", dp[n][m]);
    
    return 0;
}
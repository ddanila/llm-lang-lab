#include <stdio.h>
#include <string.h>

int main(void) {
    char line1[82], line2[82];
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;
    
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    
    while (len1 > 0 && line1[len1-1] == '\n') len1--;
    while (len2 > 0 && line2[len2-1] == '\n') len2--;
    
    int dp[82][82];
    for (int i = 0; i <= (int)len1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= (int)len2; j++) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= (int)len1; i++) {
        for (int j = 1; j <= (int)len2; j++) {
            int cost = (line1[i-1] == line2[j-1]) ? 0 : 1;
            dp[i][j] = dp[i-1][j-1] + cost;
            if (dp[i-1][j] + 1 < dp[i][j]) dp[i][j] = dp[i-1][j] + 1;
            if (dp[i][j-1] + 1 < dp[i][j]) dp[i][j] = dp[i][j-1] + 1;
        }
    }
    
    printf("%d\n", dp[(int)len1][(int)len2]);
    return 0;
}
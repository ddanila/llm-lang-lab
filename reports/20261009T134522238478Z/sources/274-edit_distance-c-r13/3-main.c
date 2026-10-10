#include <stdio.h>
#include <string.h>

static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    char line1[82];
    char line2[82];
    
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;
    
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    
    // Remove newline characters
    while (len1 > 0 && (line1[len1 - 1] == '\n' || line1[len1 - 1] == '\r')) {
        line1[--len1] = '\0';
    }
    while (len2 > 0 && (line2[len2 - 1] == '\n' || line2[len2 - 1] == '\r')) {
        line2[--len2] = '\0';
    }
    
    if (len1 == 0) {
        printf("%zu\n", len2);
        return 0;
    }
    if (len2 == 0) {
        printf("%zu\n", len1);
        return 0;
    }
    
    int dp[len1 + 1][len2 + 1];
    
    for (size_t i = 0; i <= len1; i++) {
        dp[i][0] = (int)i;
    }
    for (size_t j = 0; j <= len2; j++) {
        dp[0][j] = (int)j;
    }
    
    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + cost);
        }
    }
    
    printf("%d\n", dp[len1][len2]);
    
    return 0;
}
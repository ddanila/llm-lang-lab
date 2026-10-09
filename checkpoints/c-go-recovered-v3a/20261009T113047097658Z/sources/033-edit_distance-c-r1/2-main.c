#include <stdio.h>
#include <string.h>

static int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    char line1[81];
    char line2[81];
    
    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        return 0;
    }
    
    // Remove newline characters if present
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    
    if (len1 > 0 && line1[len1 - 1] == '\n') {
        line1[len1 - 1] = '\0';
        len1--;
    }
    if (len2 > 0 && line2[len2 - 1] == '\n') {
        line2[len2 - 1] = '\0';
        len2--;
    }
    
    // Create DP table
    int dp[81][81];
    
    // Initialize first row and column
    for (size_t i = 0; i <= len1; i++) {
        dp[i][0] = (int)i;
    }
    for (size_t j = 0; j <= len2; j++) {
        dp[0][j] = (int)j;
    }
    
    // Fill DP table
    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            dp[i][j] = min(dp[(int)i - 1][(int)j] + 1,        // deletion
                           dp[(int)i][(int)j - 1] + 1,        // insertion
                           dp[(int)i - 1][(int)j - 1] + cost); // substitution
        }
    }
    
    printf("%d\n", dp[len1][len2]);
    
    return 0;
}
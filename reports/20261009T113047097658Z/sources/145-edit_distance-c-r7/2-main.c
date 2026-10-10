#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char line1[81];
    char line2[81];
    
    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        return 0;
    }
    
    // Remove newline characters
    size_t len1 = strlen(line1);
    if (len1 > 0 && line1[len1 - 1] == '\n') {
        line1[len1 - 1] = '\0';
        len1--;
    }
    
    size_t len2 = strlen(line2);
    if (len2 > 0 && line2[len2 - 1] == '\n') {
        line2[len2 - 1] = '\0';
        len2--;
    }
    
    // Create a temporary buffer for the DP table
    char *dp = malloc((len1 + 1) * (len2 + 1) * sizeof(char));
    if (!dp) return 0;
    
    // Initialize first row and column
    for (size_t i = 0; i <= len1; i++) {
        dp[i * (len2 + 1)] = i;
    }
    for (size_t j = 0; j <= len2; j++) {
        dp[j] = j;
    }
    
    // Fill DP table
    for (size_t i = 1; i <= len1; i++) {
        char c1 = line1[i - 1];
        for (size_t j = 1; j <= len2; j++) {
            char c2 = line2[j - 1];
            int cost = (c1 == c2) ? 0 : 1;
            
            dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + j] + 1;      // deletion
            dp[i * (len2 + 1) + j] = dp[i * (len2 + 1) + (j - 1)] + 1;      // insertion
            dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + (j - 1)] + cost; // substitution
            
            if (dp[i * (len2 + 1) + j] > dp[(i - 1) * (len2 + 1) + j]) {
                dp[i * (len2 + 1) + j] = dp[(i - 1) * (len2 + 1) + j];
            }
            if (dp[i * (len2 + 1) + j] > dp[i * (len2 + 1) + (j - 1)]) {
                dp[i * (len2 + 1) + j] = dp[i * (len2 + 1) + (j - 1)];
            }
        }
    }
    
    int result = dp[len1 * (len2 + 1) + len2];
    printf("%d\n", result);
    
    free(dp);
    return 0;
}
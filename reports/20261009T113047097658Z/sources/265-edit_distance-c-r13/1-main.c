#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char line1[82], line2[82];
    
    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        return 0;
    }
    
    // Remove newline characters
    size_t len1 = strlen(line1);
    if (len1 > 0 && line1[len1-1] == '\n') {
        line1[len1-1] = '\0';
        len1--;
    }
    
    size_t len2 = strlen(line2);
    if (len2 > 0 && line2[len2-1] == '\n') {
        line2[len2-1] = '\0';
        len2--;
    }
    
    // Use dynamic allocation for DP table to handle up to 80 chars
    int *dp = malloc((len1 + 1) * (len2 + 1) * sizeof(int));
    if (!dp) return 0;
    
    // Initialize first row and column
    for (int i = 0; i <= len1; i++) {
        dp[i * (len2 + 1)] = i;
    }
    for (int j = 0; j <= len2; j++) {
        dp[j] = j;
    }
    
    // Fill DP table
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (line1[i-1] == line2[j-1]) ? 0 : 1;
            dp[i * (len2 + 1) + j] = min(
                dp[(i-1) * (len2 + 1) + j] + 1,      // deletion
                dp[i * (len2 + 1) + (j-1)] + 1,      // insertion
                dp[(i-1) * (len2 + 1) + (j-1)] + cost // substitution
            );
        }
    }
    
    int result = dp[len1 * (len2 + 1) + len2];
    printf("%d\n", result);
    
    free(dp);
    return 0;
}

int min(int a, int b) {
    return a < b ? a : b;
}
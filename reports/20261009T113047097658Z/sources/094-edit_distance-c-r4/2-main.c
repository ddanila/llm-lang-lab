#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *line1 = malloc(82);
    char *line2 = malloc(82);
    if (!line1 || !line2) return 1;
    
    if (fgets(line1, 82, stdin) == NULL) line1[0] = '\0';
    if (fgets(line2, 82, stdin) == NULL) line2[0] = '\0';
    
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    
    // Remove trailing newline if present
    if (len1 > 0 && line1[len1 - 1] == '\n') {
        line1[len1 - 1] = '\0';
        len1--;
    }
    if (len2 > 0 && line2[len2 - 1] == '\n') {
        line2[len2 - 1] = '\0';
        len2--;
    }
    
    // DP table
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
            dp[i][j] = 1 + dp[i - 1][j - 1]; // substitution
            if (dp[i - 1][j] < dp[i][j]) {
                dp[i][j] = dp[i - 1][j] + 1; // deletion
            }
            if (dp[i][j - 1] < dp[i][j]) {
                dp[i][j] = dp[i][j - 1] + 1; // insertion
            }
        }
    }
    
    printf("%d\n", dp[len1][len2]);
    
    free(line1);
    free(line2);
    return 0;
}
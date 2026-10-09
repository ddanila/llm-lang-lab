#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char line1[81], line2[81];
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;

    size_t len1 = strlen(line1);
    while (len1 > 0 && line1[len1 - 1] == '\n') len1--;
    size_t len2 = strlen(line2);
    while (len2 > 0 && line2[len2 - 1] == '\n') len2--;

    int dp[81][81];
    for (size_t i = 0; i <= len1; i++) {
        dp[i][0] = (int)i;
    }
    for (size_t j = 0; j <= len2; j++) {
        dp[0][j] = (int)j;
    }

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            dp[i][j] = dp[i - 1][j - 1] + cost;      // substitution or match
            if (dp[i - 1][j] < dp[i][j]) dp[i][j] = dp[i - 1][j] + 1;    // deletion
            if (dp[i][j - 1] < dp[i][j]) dp[i][j] = dp[i][j - 1] + 1;    // insertion
        }
    }

    printf("%d\n", dp[len1][len2]);
    return 0;
}
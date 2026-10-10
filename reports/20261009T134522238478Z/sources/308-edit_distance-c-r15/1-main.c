#include <stdio.h>
#include <string.h>

int main(void) {
    char line1[82], line2[82];
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;

    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    while (len1 > 0 && line1[len1 - 1] == '\n') line1[--len1] = '\0';
    while (len2 > 0 && line2[len2 - 1] == '\n') line2[--len2] = '\0';

    size_t m = len1, n = len2;
    if (m == 0) {
        printf("%zu\n", n);
        return 0;
    }
    if (n == 0) {
        printf("%zu\n", m);
        return 0;
    }

    int dp[81][81];
    for (size_t i = 0; i <= m; ++i) dp[i][0] = (int)i;
    for (size_t j = 0; j <= n; ++j) dp[0][j] = (int)j;

    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            dp[i][j] = 1 + dp[i - 1][j - 1];
            if (dp[i - 1][j] < dp[i][j]) dp[i][j] = dp[i - 1][j] + 1;
            if (dp[i][j - 1] < dp[i][j]) dp[i][j] = dp[i][j - 1] + 1;
        }
    }

    printf("%d\n", dp[m][n]);
    return 0;
}
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

    size_t m = len1;
    size_t n = len2;

    if (m == 0) {
        printf("%zu\n", n);
        return 0;
    }
    if (n == 0) {
        printf("%zu\n", m);
        return 0;
    }

    size_t dp[m + 1][n + 1];

    for (size_t i = 0; i <= m; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= n; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            dp[i][j] = dp[i - 1][j - 1] + cost;
            size_t d_del = dp[i - 1][j] + 1;
            if (d_del < dp[i][j]) dp[i][j] = d_del;
            size_t d_ins = dp[i][j - 1] + 1;
            if (d_ins < dp[i][j]) dp[i][j] = d_ins;
        }
    }

    printf("%zu\n", dp[m][n]);

    return 0;
}
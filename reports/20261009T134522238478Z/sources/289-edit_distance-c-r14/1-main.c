#include <stdio.h>
#include <string.h>

int main(void) {
    char line1[82], line2[82];
    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        return 0;
    }

    size_t n = strlen(line1);
    size_t m = strlen(line2);

    // Remove newline characters if present
    while (n > 0 && (line1[n-1] == '\n' || line1[n-1] == '\r')) {
        line1[--n] = '\0';
    }
    while (m > 0 && (line2[m-1] == '\n' || line2[m-1] == '\r')) {
        line2[--m] = '\0';
    }

    // DP array
    int dp[82][82];

    for (size_t i = 0; i <= n; i++) {
        dp[i][0] = (int)i;
    }
    for (size_t j = 0; j <= m; j++) {
        dp[0][j] = (int)j;
    }

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            int cost = (line1[i-1] == line2[j-1]) ? 0 : 1;
            dp[i][j] = 1 + dp[i-1][j];       // deletion
            if (dp[i-1][j+1] < dp[i][j]) {   // substitution/insertion logic via previous row col
                int val = dp[i-1][j+1];
                if (val < dp[i][j]) dp[i][j] = val;
            }
            if (dp[i+1][j-1] < dp[i][j]) {   // substitution/insertion logic via previous row col
                int val = dp[i+1][j-1];
                if (val < dp[i][j]) dp[i][j] = val;
            }
        }
    }

    printf("%d\n", dp[n][m]);
    return 0;
}
#include <stdio.h>
#include <string.h>

int main(void) {
    char line1[81], line2[81];
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;
    
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    
    while (len1 > 0 && line1[len1 - 1] == '\n') line1[--len1] = '\0';
    while (len2 > 0 && line2[len2 - 1] == '\n') line2[--len2] = '\0';
    
    size_t n = len1, m = len2;
    int dp[m + 1];
    for (size_t j = 0; j <= m; ++j) dp[j] = j;
    
    for (size_t i = 1; i <= n; ++i) {
        int prev = dp[0];
        dp[0] = i;
        for (size_t j = 1; j <= m; ++j) {
            int temp = dp[j];
            if (line1[i - 1] == line2[j - 1]) {
                dp[j] = prev;
            } else {
                int del = dp[j] + 1;      // deletion from line1
                int ins = prev + 1;      // insertion into line1
                int sub = temp + 1;      // substitution
                if (del < ins) {
                    dp[j] = (ins < sub) ? ins : sub;
                } else {
                    dp[j] = (sub < ins) ? sub : ins;
                }
            }
            prev = temp;
        }
    }
    
    printf("%d\n", dp[m]);
    return 0;
}
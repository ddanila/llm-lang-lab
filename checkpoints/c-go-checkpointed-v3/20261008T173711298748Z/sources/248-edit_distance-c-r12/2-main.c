#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int min(int a, int b) { return a < b ? a : b; }

int main(void) {
    char line1[81];
    char line2[81];

    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;

    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);

    if (len1 > 0 && line1[len1 - 1] == '\n') line1[len1 - 1] = '\0';
    if (len2 > 0 && line2[len2 - 1] == '\n') line2[len2 - 1] = '\0';

    int n = (int)len1;
    int m = (int)len2;

    // Use two rows to save space
    int prev[81];
    int curr[81];

    for (int j = 0; j <= m; j++) {
        prev[j] = j;
    }

    for (int i = 1; i <= n; i++) {
        curr[0] = i;
        for (int j = 1; j <= m; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            curr[j] = min(min(prev[j] + 1, curr[j - 1] + 1), prev[j - 1] + cost);
        }
        for (int j = 0; j <= m; j++) {
            prev[j] = curr[j];
        }
    }

    printf("%d\n", prev[m]);

    return 0;
}
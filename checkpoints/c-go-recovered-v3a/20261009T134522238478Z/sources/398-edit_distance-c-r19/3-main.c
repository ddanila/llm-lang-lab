#include <stdio.h>
#include <string.h>

static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    char line1[82] = "";
    char line2[82] = "";

    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;

    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);

    // Remove newline characters - but only if they exist and we're not at length 0
    if (len1 > 0 && line1[len1 - 1] == '\n') {
        memmove(line1, line1 + 1, len1);
        len1--;
    }
    if (len2 > 0 && line2[len2 - 1] == '\n') {
        memmove(line2, line2 + 1, len2);
        len2--;
    }

    // DP array for edit distance
    int prev[82];
    int curr[82];

    for (size_t i = 0; i <= len1; i++) {
        if (i == 0) prev[i] = i;
        else prev[i] = prev[i - 1] + 1;
    }

    for (size_t j = 0; j <= len2; j++) {
        if (j == 0) curr[j] = j;
        else curr[j] = curr[j - 1] + 1;
    }

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            curr[j] = min(prev[j] + 1, min(curr[j - 1] + 1, prev[j - 1] + cost));
        }
        for (size_t j = 0; j <= len2; j++) {
            prev[j] = curr[j];
        }
    }

    printf("%d\n", prev[len2]);

    return 0;
}
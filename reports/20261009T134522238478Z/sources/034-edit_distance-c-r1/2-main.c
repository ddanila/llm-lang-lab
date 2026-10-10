#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static inline int min(int a, int b) {
    return a < b ? a : b;
}

int main(void) {
    char line1[82] = {0};
    char line2[82] = {0};

    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        return 0;
    }

    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);

    if (line1[len1 - 1] == '\n') {
        line1[--len1] = '\0';
    }
    if (line2[len2 - 1] == '\n') {
        line2[--len2] = '\0';
    }

    size_t m = len1;
    size_t n = len2;

    int prev[82];
    int curr[82];

    for (size_t i = 0; i <= m; ++i) {
        prev[i] = (int)i;
    }

    for (size_t j = 1; j <= n; ++j) {
        curr[0] = (int)j;
        for (size_t i = 1; i <= m; ++i) {
            int cost = line1[i - 1] == line2[j - 1] ? 0 : 1;
            curr[i] = min(
                prev[i] + 1,
                min(curr[i - 1] + 1, prev[i - 1] + cost)
            );
        }
        for (size_t i = 0; i <= m; ++i) {
            prev[i] = curr[i];
        }
    }

    printf("%d\n", prev[m]);

    return 0;
}
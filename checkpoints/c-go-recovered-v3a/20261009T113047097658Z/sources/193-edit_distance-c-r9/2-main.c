#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    char line1[81] = "";
    char line2[81] = "";

    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        return 0;
    }

    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);

    if (len1 > 0 && line1[len1 - 1] == '\n') {
        line1[len1 - 1] = '\0';
        len1--;
    }
    if (len2 > 0 && line2[len2 - 1] == '\n') {
        line2[len2 - 1] = '\0';
        len2--;
    }

    size_t n = len1 + 1;
    size_t m = len2 + 1;

    int *prev = malloc(m * sizeof(int));
    int *curr = malloc(m * sizeof(int));

    if (!prev || !curr) {
        return 0;
    }

    for (size_t j = 0; j < m; j++) {
        prev[j] = (int)j;
    }

    for (size_t i = 1; i <= len1; i++) {
        curr[0] = (int)i;
        for (size_t j = 1; j <= len2; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            curr[j] = min(min(prev[j] + 1, curr[j - 1] + 1), prev[j - 1] + cost);
        }
        for (size_t j = 0; j < m; j++) {
            prev[j] = curr[j];
        }
    }

    int result = prev[len2];
    printf("%d\n", result);

    free(prev);
    free(curr);

    return 0;
}
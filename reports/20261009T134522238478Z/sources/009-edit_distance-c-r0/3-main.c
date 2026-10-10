#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    char line1[82];
    char line2[82];

    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;

    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);

    if (len1 > 0 && line1[len1 - 1] == '\n') line1[--len1] = '\0';
    if (len2 > 0 && line2[len2 - 1] == '\n') line2[--len2] = '\0';

    size_t m = len1;
    size_t n = len2;

    int *prev = malloc((m + 1) * sizeof(int));
    int *curr = malloc((n + 1) * sizeof(int));

    if (!prev || !curr) {
        free(prev);
        free(curr);
        return 0;
    }

    for (size_t i = 0; i <= m; i++) prev[i] = (int)i;
    for (size_t j = 0; j <= n; j++) curr[j] = (int)j;

    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            curr[j] = min(curr[j - 1], prev[j]) + 1;      // deletion from s1
            curr[j] = min(curr[j], prev[j - 1] + cost);   // substitution/insertion
        }
        for (size_t j = 0; j <= n; j++) prev[j] = curr[j];
    }

    int result = curr[n];

    free(prev);
    free(curr);

    printf("%d\n", result);

    return 0;
}
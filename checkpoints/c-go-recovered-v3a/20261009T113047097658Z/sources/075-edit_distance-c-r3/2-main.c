#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int min(int a, int b) { return (a < b) ? a : b; }

int main(void) {
    char *line1 = malloc(82);
    char *line2 = malloc(82);
    if (!line1 || !line2) return 1;

    if (fgets(line1, 82, stdin) == NULL) {
        free(line1); free(line2);
        return 0;
    }
    if (fgets(line2, 82, stdin) == NULL) {
        free(line1); free(line2);
        return 0;
    }

    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);

    if (len1 > 0 && line1[len1 - 1] == '\n') line1[len1 - 1] = '\0';
    if (len2 > 0 && line2[len2 - 1] == '\n') line2[len2 - 1] = '\0';

    int m = len1;
    int n = len2;

    int *prev = calloc(n + 1, sizeof(int));
    int *curr = calloc(n + 1, sizeof(int));
    if (!prev || !curr) { free(prev); free(curr); return 1; }

    for (int j = 0; j <= n; j++) prev[j] = j;

    for (int i = 1; i <= m; i++) {
        curr[0] = i;
        for (int j = 1; j <= n; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            curr[j] = min(prev[j] + 1, min(curr[j - 1] + 1, prev[j - 1] + cost));
        }
        for (int j = 0; j <= n; j++) prev[j] = curr[j];
    }

    printf("%d\n", prev[n]);

    free(prev);
    free(curr);
    free(line1);
    free(line2);
    return 0;
}
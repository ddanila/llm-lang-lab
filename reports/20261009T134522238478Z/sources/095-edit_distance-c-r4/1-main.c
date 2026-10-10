#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char line1[82];
    char line2[82];

    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;

    // Remove trailing newline if present
    size_t len1 = strlen(line1);
    if (len1 > 0 && line1[len1 - 1] == '\n') {
        line1[len1 - 1] = '\0';
        len1--;
    }

    size_t len2 = strlen(line2);
    if (len2 > 0 && line2[len2 - 1] == '\n') {
        line2[len2 - 1] = '\0';
        len2--;
    }

    // DP array
    int d[82][82];
    for (size_t i = 0; i <= len1; i++) d[i][0] = (int)i;
    for (size_t j = 0; j <= len2; j++) d[0][j] = (int)j;

    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            d[i][j] = d[i - 1][j - 1] + cost;
            int del = d[i - 1][j] + 1;
            int ins = d[i][j - 1] + 1;
            if (del < d[i][j]) d[i][j] = del;
            if (ins < d[i][j]) d[i][j] = ins;
        }
    }

    printf("%d\n", d[len1][len2]);
    return 0;
}
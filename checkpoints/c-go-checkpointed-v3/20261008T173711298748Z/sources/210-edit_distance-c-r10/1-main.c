#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char line1[81];
    char line2[81];

    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        return 0;
    }

    // Remove trailing newline characters
    size_t len1 = strlen(line1);
    while (len1 > 0 && (line1[len1 - 1] == '\n' || line1[len1 - 1] == '\r')) {
        line1[--len1] = '\0';
    }

    size_t len2 = strlen(line2);
    while (len2 > 0 && (line2[len2 - 1] == '\n' || line2[len2 - 1] == '\r')) {
        line2[--len2] = '\0';
    }

    // Use two rows for space optimization
    int prev[81];
    int curr[81];

    for (size_t i = 0; i <= len1; i++) {
        prev[i] = (int)i;
    }

    for (size_t j = 0; j <= len2; j++) {
        curr[j] = (int)j;
    }

    for (size_t j = 1; j <= len2; j++) {
        for (size_t i = 1; i <= len1; i++) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            curr[j] = min(prev[j] + 1, min(curr[j - 1] + 1, prev[j - 1] + cost));
        }
        for (size_t i = 0; i <= len1; i++) {
            prev[i] = curr[i];
        }
    }

    printf("%d\n", prev[len2]);

    return 0;
}

int min(int a, int b) {
    return a < b ? a : b;
}
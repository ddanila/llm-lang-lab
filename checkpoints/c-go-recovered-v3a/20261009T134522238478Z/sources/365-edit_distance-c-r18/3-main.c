#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    char *line1 = NULL;
    char *line2 = NULL;
    size_t cap1 = 82;
    size_t cap2 = 82;
    size_t len1 = 0;
    size_t len2 = 0;

    // Read line 1
    {
        int c;
        while ((c = getchar()) != EOF && c != '\n') {
            if (len1 == cap1 - 1) {
                cap1 *= 2;
                char *new_line = realloc(line1, cap1);
                if (!new_line) return 1;
                line1 = new_line;
            }
            line1[len1++] = (char)c;
        }
    }

    // Read line 2
    {
        int c;
        while ((c = getchar()) != EOF && c != '\n') {
            if (len2 == cap2 - 1) {
                cap2 *= 2;
                char *new_line = realloc(line2, cap2);
                if (!new_line) return 1;
                line2 = new_line;
            }
            line2[len2++] = (char)c;
        }
    }

    // Compute Levenshtein distance using dynamic programming
    int *prev = malloc(len2 + 1);
    int *curr = malloc(len2 + 1);
    if (!prev || !curr) return 1;

    for (size_t i = 0; i <= len2; ++i) {
        prev[i] = (int)i;
    }

    for (size_t j = 0; j < len1; ++j) {
        curr[0] = (int)(j + 1);
        for (size_t i = 0; i < len2; ++i) {
            int cost = (line1[j] == line2[i]) ? 0 : 1;
            curr[i + 1] = min(min(prev[i + 1] + 1, curr[i] + 1), prev[i] + cost);
        }
        memcpy(prev, curr, len2 + 1);
    }

    int result = prev[len2];

    free(line1);
    free(line2);
    free(prev);
    free(curr);

    printf("%d\n", result);

    return 0;
}
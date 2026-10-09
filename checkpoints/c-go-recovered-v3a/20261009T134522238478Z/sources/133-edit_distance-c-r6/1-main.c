#include <stdio.h>
#include <string.h>

int main(void) {
    char line1[82] = "";
    char line2[82] = "";

    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        // If second line is missing, treat as empty string
        line2[0] = '\0';
    }

    // Remove newline characters if present
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

    // Create DP table
    int dist[82][82];
    
    // Initialize first row and column
    for (size_t i = 0; i <= len1; i++) {
        dist[i][0] = i;
    }
    for (size_t j = 0; j <= len2; j++) {
        dist[0][j] = j;
    }

    // Fill DP table
    for (size_t i = 1; i <= len1; i++) {
        for (size_t j = 1; j <= len2; j++) {
            int cost = (line1[i-1] == line2[j-1]) ? 0 : 1;
            dist[i][j] = min(dist[i-1][j] + 1,      // deletion
                             dist[i][j-1] + 1,       // insertion
                             dist[i-1][j-1] + cost); // substitution
        }
    }

    printf("%d\n", dist[len1][len2]);

    return 0;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}
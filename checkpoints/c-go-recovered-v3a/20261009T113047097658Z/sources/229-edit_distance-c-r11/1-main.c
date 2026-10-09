#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char line1[82] = "";
    char line2[82] = "";
    
    if (fgets(line1, sizeof(line1), stdin) == NULL) {
        return 0;
    }
    if (fgets(line2, sizeof(line2), stdin) == NULL) {
        return 0;
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
    
    // Create a dynamic DP table
    int *dp = malloc((len1 + 1) * sizeof(int));
    if (dp == NULL) return 1;
    
    // Initialize first row and column
    for (int i = 0; i <= len1; i++) {
        dp[i] = i;
    }
    
    // Create second row on stack
    int *prev_row = malloc((len1 + 1) * sizeof(int));
    if (prev_row == NULL) { free(dp); return 1; }
    
    for (int j = 0; j <= len2; j++) {
        prev_row[j] = j;
    }
    
    // Fill DP table
    for (int i = 1; i <= len1; i++) {
        int *curr_row = &dp[i];
        for (int j = 1; j <= len2; j++) {
            if (line1[i - 1] == line2[j - 1]) {
                curr_row[j] = prev_row[j - 1];
            } else {
                int sub = prev_row[j - 1];
                int del = curr_row[j - 1] + 1;
                int ins = prev_row[j] + 1;
                curr_row[j] = (sub < del) ? (sub < ins ? sub : ins) : ((del < ins) ? del : ins);
            }
        }
        // Copy curr_row to prev_row for next iteration
        for (int j = 0; j <= len2; j++) {
            prev_row[j] = dp[j];
        }
    }
    
    int result = dp[len1];
    
    free(dp);
    free(prev_row);
    
    printf("%d\n", result);
    
    return 0;
}
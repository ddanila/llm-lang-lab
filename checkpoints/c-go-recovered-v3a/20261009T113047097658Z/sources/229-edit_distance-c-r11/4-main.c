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
    
    // Allocate DP table: dp[i][j] = edit distance between s1[0..i-1] and s2[0..j-1]
    int *dp = malloc((len1 + 1) * sizeof(int));
    if (dp == NULL) return 1;
    
    // Initialize first row (s1 is empty)
    for (size_t j = 0; j <= len2; j++) {
        dp[j] = (int)j;
    }
    
    // Allocate second row
    int *new_row = malloc((len2 + 1) * sizeof(int));
    if (new_row == NULL) {
        free(dp);
        return 1;
    }
    
    // Process each character of s1
    for (size_t i = 1; i <= len1; i++) {
        new_row[0] = (int)i;  // distance to empty string s2
        
        for (size_t j = 1; j <= len2; j++) {
            if (line1[i - 1] == line2[j - 1]) {
                new_row[j] = dp[j - 1];
            } else {
                int sub = dp[j - 1];      // substitution
                int del = new_row[j - 1] + 1;  // deletion from s1
                int ins = dp[j] + 1;      // insertion into s1
                
                if (sub <= del && sub <= ins) {
                    new_row[j] = sub;
                } else if (del <= ins) {
                    new_row[j] = del;
                } else {
                    new_row[j] = ins;
                }
            }
        }
        
        // Copy new_row to dp for next iteration
        for (size_t j = 0; j <= len2; j++) {
            dp[j] = new_row[j];
        }
    }
    
    printf("%d\n", dp[len2]);
    
    free(dp);
    free(new_row);
    
    return 0;
}
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
    
    // Create a dynamic DP table with two rows only
    int *prev_row = malloc((len2 + 1) * sizeof(int));
    int *curr_row = malloc((len2 + 1) * sizeof(int));
    if (prev_row == NULL || curr_row == NULL) {
        free(prev_row);
        free(curr_row);
        return 1;
    }
    
    // Initialize first row (for empty string s1)
    for (size_t j = 0; j <= len2; j++) {
        prev_row[j] = (int)j;
    }
    
    // Fill DP table
    for (size_t i = 1; i <= len1; i++) {
        curr_row[0] = (int)i;  // first column (for empty string s2)
        for (size_t j = 1; j <= len2; j++) {
            if (line1[i - 1] == line2[j - 1]) {
                curr_row[j] = prev_row[j - 1];
            } else {
                int sub = prev_row[j - 1];     // substitution
                int del = curr_row[j - 1] + 1; // deletion from s1
                int ins = prev_row[j] + 1;     // insertion into s1
                if (sub <= del && sub <= ins) {
                    curr_row[j] = sub;
                } else if (del <= ins) {
                    curr_row[j] = del;
                } else {
                    curr_row[j] = ins;
                }
            }
        }
        // Copy curr_row to prev_row for next iteration
        for (size_t j = 0; j <= len2; j++) {
            prev_row[j] = curr_row[j];
        }
    }
    
    int result = prev_row[len2];
    
    free(prev_row);
    free(curr_row);
    
    printf("%d\n", result);
    
    return 0;
}
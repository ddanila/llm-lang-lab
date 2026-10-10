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
    
    // Allocate DP table with two rows
    int *row1 = malloc((len2 + 1) * sizeof(int));
    int *row2 = malloc((len2 + 1) * sizeof(int));
    if (row1 == NULL || row2 == NULL) {
        free(row1);
        free(row2);
        return 1;
    }
    
    // Initialize row1: distance from empty string to s2[0..j]
    for (size_t j = 0; j <= len2; j++) {
        row1[j] = (int)j;
    }
    
    // Process each character of s1
    for (size_t i = 1; i <= len1; i++) {
        // First element: distance from s1[0..i-1] to empty string
        row2[0] = (int)i;
        
        // Compute rest of the row
        for (size_t j = 1; j <= len2; j++) {
            if (line1[i - 1] == line2[j - 1]) {
                row2[j] = row1[j - 1];
            } else {
                int sub = row1[j - 1];      // substitution
                int del = row2[j - 1] + 1;  // deletion
                int ins = row1[j] + 1;      // insertion
                if (sub <= del && sub <= ins) {
                    row2[j] = sub;
                } else if (del <= ins) {
                    row2[j] = del;
                } else {
                    row2[j] = ins;
                }
            }
        }
        
        // Copy row2 to row1 for next iteration
        for (size_t j = 0; j <= len2; j++) {
            row1[j] = row2[j];
        }
    }
    
    printf("%d\n", row1[len2]);
    
    free(row1);
    free(row2);
    
    return 0;
}
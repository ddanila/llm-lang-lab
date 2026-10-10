#include <stdio.h>
#include <string.h>

int main(void) {
    char line1[81], line2[81];
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;
    
    size_t len1 = strlen(line1);
    size_t len2 = strlen(line2);
    
    while (len1 > 0 && line1[len1 - 1] == '\n') line1[--len1] = '\0';
    while (len2 > 0 && line2[len2 - 1] == '\n') line2[--len2] = '\0';
    
    size_t n = len1, m = len2;
    int prev_row[82];
    int curr_row[82];
    
    for (size_t j = 0; j <= m; ++j) {
        prev_row[j] = j;
        curr_row[j] = j;
    }
    
    for (size_t i = 1; i <= n; ++i) {
        int diag = prev_row[0];
        prev_row[0] = i;
        for (size_t j = 1; j <= m; ++j) {
            int cost = (line1[i - 1] == line2[j - 1]) ? 0 : 1;
            curr_row[j] = min({prev_row[j] + cost, diag + 1, prev_row[j - 1] + cost});
            diag = prev_row[j];
        }
        for (size_t j = 0; j <= m; ++j) {
            prev_row[j] = curr_row[j];
        }
    }
    
    printf("%d\n", prev_row[m]);
    return 0;
}

int min(int a, int b) { return a < b ? a : b; }
int min3(int a, int b, int c) { return min(min(a, b), c); }
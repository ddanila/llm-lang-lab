#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char buf[10000];
    size_t len = 0;
    
    // Read input until EOF or buffer full
    int c;
    while ((c = getchar()) != EOF && len < (sizeof(buf) - 1)) {
        if (isalpha(c)) {
            buf[len++] = (char)tolower(c);
        } else {
            buf[len++] = '\0'; // End current word
            if (len > 0) {
                char *word = buf;
                size_t wlen = strnlen(word, len);
                
                // Find or insert this word in sorted order
                int left = 0, right = 1;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    int cmp = strcmp(word, words[mid]);
                    if (cmp == 0) {
                        counts[mid]++;
                        goto done_search;
                    } else if (cmp < 0) {
                        right = mid;
                    } else {
                        left = mid + 1;
                    }
                }
                
                // Insert at 'left'
                memmove(words + left + 1, words + left, (right - left + 1) * sizeof(char *));
                words[left] = strdup(word);
                counts[left] = 1;
                
            done_search:;
        }
        
        // Continue reading after separator
        if (!isalpha(c)) {
            len = 0;
        }
    }
    
    // Output results
    for (int i = 0; i < n; i++) {
        printf("%s %zu\n", words[i], counts[i]);
    }
    
    return 0;
}
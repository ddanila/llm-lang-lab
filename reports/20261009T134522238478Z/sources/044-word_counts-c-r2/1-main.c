#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry*)a)->word, ((WordEntry*)b)->word);
}

int main(void) {
    unsigned char buf[10005];
    size_t n = 0;
    
    int c;
    while ((c = getchar()) != EOF && n < 10000) {
        buf[n++] = (unsigned char)c;
    }
    
    if (n == 0) {
        return 0;
    }
    
    // Find all words and count them
    int word_count = 0;
    size_t i = 0;
    while (i < n) {
        if (isalpha(buf[i])) {
            size_t start = i;
            while (i < n && isalpha(buf[i])) {
                i++;
            }
            size_t len = i - start;
            
            // Convert to lowercase
            for (size_t j = 0; j < len; j++) {
                buf[start + j] = tolower((unsigned char)buf[start + j]);
            }
            
            if (word_count == 0 || strcmp(buf, &buf[start], word_count->word) > 0) {
                // Add new word or update existing?
                // We need a dynamic structure. Let's use a simpler approach.
            }
        } else {
            i++;
        }
    }
    
    return 0;
}
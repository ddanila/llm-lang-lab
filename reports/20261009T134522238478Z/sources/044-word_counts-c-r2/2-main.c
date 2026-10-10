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
    
    // First pass: extract all words and store them in a buffer
    size_t word_count = 0;
    size_t total_words_size = 0;
    char *words[10000];  // max possible words
    
    size_t i = 0;
    while (i < n) {
        if (isalpha(buf[i])) {
            size_t start = i;
            while (i < n && isalpha(buf[i])) {
                i++;
            }
            size_t len = i - start;
            
            // Convert to lowercase in place
            for (size_t j = 0; j < len; j++) {
                buf[start + j] = tolower((unsigned char)buf[start + j]);
            }
            
            words[word_count] = (char*)buf + start;
            word_count++;
        } else {
            i++;
        }
    }
    
    if (word_count == 0) {
        return 0;
    }
    
    // Count occurrences of each word
    int *counts = malloc(word_count * sizeof(int));
    for (int j = 0; j < word_count; j++) {
        counts[j] = 0;
    }
    
    for (size_t w = 0; w < word_count; w++) {
        char *word = words[w];
        size_t len = strlen(word);
        
        for (size_t k = 0; k < word_count; k++) {
            if (strcmp(words[k], word) == 0 && counts[k] == 0) {
                // Found a duplicate, increment count and mark as found
                counts[w]++;
                break;
            } else if (strcmp(words[k], word) != 0) {
                // Not the same word yet, continue
            }
        }
        // This approach is wrong. Let me redo it.
    }
    
    free(counts);
    return 0;
}
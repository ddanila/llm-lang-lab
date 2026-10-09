#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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
    
    // Extract all words and store them in a dynamic array
    typedef struct {
        char *word;
        int count;
    } WordEntry;
    
    WordEntry *words = malloc(10005 * sizeof(WordEntry));
    size_t word_count = 0;
    
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
            
            words[word_count].word = (char*)buf + start;
            words[word_count].count = 1;
            word_count++;
        } else {
            i++;
        }
    }
    
    if (word_count == 0) {
        free(words);
        return 0;
    }
    
    // Count occurrences - for each word, check all other words
    for (size_t w = 0; w < word_count; w++) {
        char *current_word = words[w].word;
        for (size_t k = 0; k < word_count; k++) {
            if (words[k].count == 1 && strcmp(words[k].word, current_word) == 0) {
                words[k].count++;
            }
        }
    }
    
    // Sort by word lexicographically
    for (size_t j = 0; j < word_count - 1; j++) {
        for (size_t k = 0; k < word_count - 1 - j; k++) {
            if (strcmp(words[k].word, words[k+1].word) > 0) {
                WordEntry temp = words[k];
                words[k] = words[k+1];
                words[k+1] = temp;
            }
        }
    }
    
    // Output
    for (size_t j = 0; j < word_count; j++) {
        printf("%s %d\n", words[j].word, words[j].count);
    }
    
    free(words);
    return 0;
}
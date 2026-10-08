#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    unsigned char buf[10005];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    
    // Skip leading non-letters to find first word
    size_t wstart = 0;
    while (wstart < len && !isalpha((unsigned char)buf[wstart])) {
        wstart++;
    }
    
    if (wstart >= len) {
        return 0; // No letters found
    }
    
    // Count letters in first word
    size_t word_end = wstart;
    while (word_end < len && isalpha((unsigned char)buf[word_end])) {
        word_end++;
    }
    
    if (word_end == wstart) {
        return 0; // No words found
    }
    
    typedef struct { char *word; int count; } WordEntry;
    WordEntry *words = NULL;
    int num_words = 0;
    
    while (wstart < len) {
        size_t word_end = wstart;
        while (word_end < len && isalpha((unsigned char)buf[word_end])) {
            word_end++;
        }
        size_t word_len = word_end - wstart;
        
        // Allocate new word entry
        WordEntry *entry = malloc(sizeof(WordEntry));
        if (!entry) break;
        
        entry->word = malloc(word_len + 1);
        if (!entry->word) {
            free(entry);
            break;
        }
        
        for (size_t i = 0; i < word_len; i++) {
            entry->word[i] = tolower((unsigned char)buf[wstart + i]);
        }
        entry->word[word_len] = '\0';
        entry->count = 1;
        
        // Check for existing word with same lowercase value
        int exists = 0;
        for (int i = 0; i < num_words; i++) {
            if (strcmp(entry->word, words[i].word) == 0) {
                words[i].count++;
                exists = 1;
                break;
            }
        }
        
        if (!exists) {
            words[num_words++] = *entry;
        }
        
        free(entry);
        wstart = word_end;
    }
    
    // Sort by ASCII lexicographic order of the lowercase word (bubble sort)
    for (int i = 0; i < num_words - 1; i++) {
        for (int j = i + 1; j < num_words; j++) {
            if (strcmp(words[i].word, words[j].word) > 0) {
                WordEntry tmp = words[i];
                words[i] = words[j];
                words[j] = tmp;
            }
        }
    }
    
    // Output
    for (int i = 0; i < num_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    // Cleanup
    for (int i = 0; i < num_words; i++) {
        free(words[i].word);
    }
    free(words);
    
    return 0;
}
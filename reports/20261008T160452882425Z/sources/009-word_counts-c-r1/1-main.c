#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    unsigned char buf[10005];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    
    // Find first letter position to skip leading non-letters
    size_t start = 0;
    while (start < len && !isalpha(buf[start])) {
        start++;
    }
    
    if (start >= len) {
        return 0; // No letters found
    }
    
    // Find first word boundary after start
    size_t wstart = start;
    while (wstart < len && isalpha(buf[wstart])) {
        wstart++;
    }
    
    if (wstart == start) {
        return 0; // No words found
    }
    
    // Count letters in first word
    size_t wlen = wstart - start;
    
    // Collect all words
    typedef struct { char *word; int count; } WordEntry;
    WordEntry *words = NULL;
    int num_words = 0;
    
    while (wstart < len) {
        size_t word_end = wstart;
        while (word_end < len && isalpha(buf[word_end])) {
            word_end++;
        }
        size_t word_len = word_end - wstart;
        
        // Skip if word too long (though input is max 10000 bytes)
        if (word_len > 10000) {
            wstart = word_end;
            continue;
        }
        
        // Allocate new word entry
        WordEntry *entry = malloc(sizeof(WordEntry));
        if (!entry) break;
        
        // Count existing words with same lowercase version
        int found = 0;
        for (int i = 0; i < num_words; i++) {
            if (strcmp(words[i].word, &buf[wstart]) == 0 && 
                strcmp(tolower(&buf[wstart]), words[i].word) == 0) {
                // Actually we need to compare lowercase. Let's redo this.
                break;
            }
        }
        
        // Simpler: just store original case words and convert when outputting
        // But we need case-insensitive comparison.
        // Let's store lowercase versions.
        
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
        
        free(entry); // We already added to array or found existing
        wstart = word_end;
    }
    
    // Sort by ASCII lexicographic order of the lowercase word
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
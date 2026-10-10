#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char word[10001];
    int count;
} WordEntry;

int compare_words(const void *a, const void *b) {
    const WordEntry *wa = (const WordEntry *)a;
    const WordEntry *wb = (const WordEntry *)b;
    size_t len_a = strlen(wa->word);
    size_t len_b = strlen(wb->word);
    size_t len = len_a < len_b ? len_a : len_b;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char ca = tolower((unsigned char)wa->word[i]);
        unsigned char cb = tolower((unsigned char)wb->word[i]);
        if (ca < cb) return -1;
        if (ca > cb) return 1;
    }
    return len_a - len_b;
}

int main(void) {
    char buffer[10005];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    // Handle empty input
    if (len == 0) return 0;
    
    WordEntry *words = malloc(sizeof(WordEntry));
    if (!words) return 1;
    words->count = 0;
    
    const char *p = buffer;
    while (p < buffer + len) {
        if (!isalpha((unsigned char)*p)) {
            p++;
            continue;
        }
        
        // Start of a word
        size_t wlen = 0;
        while (p < buffer + len && isalpha((unsigned char)*p)) {
            words[words->count].word[wlen++] = *p;
            p++;
        }
        
        if (wlen > 0) {
            // Convert to lowercase
            for (size_t i = 0; i < wlen; i++) {
                words[words->count].word[i] = tolower((unsigned char)words[words->count].word[i]);
            }
            
            // Check if word exists
            int found = 0;
            for (size_t i = 0; i < words->count; i++) {
                if (strcmp(words[i].word, words[words->count].word) == 0) {
                    words[i].count++;
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                // Expand array if needed
                size_t new_cap = (words->count + 1) * 2;
                WordEntry *new_words = realloc(words, sizeof(WordEntry) * new_cap);
                if (!new_words) return 1;
                words = new_words;
            }
        }
    }
    
    if (words->count > 0) {
        qsort(words, words->count, sizeof(WordEntry), compare_words);
        
        for (size_t i = 0; i < words->count; i++) {
            printf("%s %d\n", words[i].word, words[i].count);
        }
    }
    
    free(words);
    return 0;
}
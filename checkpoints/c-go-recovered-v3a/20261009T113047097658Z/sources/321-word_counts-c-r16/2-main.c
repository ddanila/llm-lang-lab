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
    
    WordEntry *words = NULL;
    size_t num_words = 0;
    size_t capacity = 0;
    
    const char *p = buffer;
    while (p < buffer + len) {
        if (!isalpha((unsigned char)*p)) {
            p++;
            continue;
        }
        
        // Start of a word
        size_t wlen = 0;
        while (p < buffer + len && isalpha((unsigned char)*p)) {
            words[num_words].word[wlen++] = *p;
            p++;
        }
        
        if (wlen > 0) {
            // Convert to lowercase
            for (size_t i = 0; i < wlen; i++) {
                words[num_words].word[i] = tolower((unsigned char)words[num_words].word[i]);
            }
            
            // Check if word exists
            int found = 0;
            for (size_t i = 0; i < num_words; i++) {
                if (strcmp(words[i].word, words[num_words].word) == 0) {
                    words[i].count++;
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                if (num_words >= capacity) {
                    capacity = capacity == 0 ? 4 : capacity * 2;
                    WordEntry *new_words = realloc(words, capacity * sizeof(WordEntry));
                    if (!new_words) return 1;
                    words = new_words;
                }
                words[num_words].count = 1;
                num_words++;
            }
        }
    }
    
    if (num_words > 0) {
        qsort(words, num_words, sizeof(WordEntry), compare_words);
        
        for (size_t i = 0; i < num_words; i++) {
            printf("%s %d\n", words[i].word, words[i].count);
        }
    }
    
    free(words);
    return 0;
}
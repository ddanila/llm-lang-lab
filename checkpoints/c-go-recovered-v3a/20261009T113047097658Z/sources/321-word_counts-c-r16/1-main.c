#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare_words(const void *a, const void *b) {
    const char *wa = (const char *)a;
    const char *wb = (const char *)b;
    while (*wa && *wb) {
        if (tolower((unsigned char)*wa) < tolower((unsigned char)*wb)) return -1;
        if (tolower((unsigned char)*wa) > tolower((unsigned char)*wb)) return 1;
        wa++; wb++;
    }
    return tolower((unsigned char)*wa) - tolower((unsigned char)*wb);
}

int main(void) {
    char buffer[10005];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    // Build a list of words and their counts
    typedef struct {
        char word[10001];
        int count;
    } WordEntry;
    
    WordEntry *words = NULL;
    size_t num_words = 0;
    size_t capacity = 0;
    
    // Parse words from buffer
    const char *p = buffer;
    while (p < buffer + len) {
        if (*p == '\n' || *p == '\r') {
            p++;
            continue;
        }
        
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
    
    // Sort words
    qsort(words, num_words, sizeof(WordEntry), compare_words);
    
    // Output
    for (size_t i = 0; i < num_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    free(words);
    return 0;
}
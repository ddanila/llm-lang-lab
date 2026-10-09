#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    char buf[10001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    // Collect words and counts
    // We'll use a simple approach: extract words into an array of structs
    // Since max bytes is 10000, we can have at most 5000 words (min word length 1)
    typedef struct { char w[10001]; size_t len; } Word;
    static Word words[5000];
    int wcount = 0;
    
    int in_word = 0;
    char current_word[10001];
    size_t cur_len = 0;
    
    for (size_t i = 0; i < n; i++) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            if (!in_word) {
                in_word = 1;
                cur_len = 0;
                // Copy to current buffer
                current_word[cur_len++] = (char)c;
            } else {
                current_word[cur_len++] = (char)c;
            }
        } else {
            if (in_word) {
                words[wcount].len = cur_len;
                memcpy(words[wcount].w, current_word, cur_len);
                wcount++;
                in_word = 0;
                cur_len = 0;
            }
        }
    }
    
    // Handle last word if any
    if (in_word) {
        words[wcount].len = cur_len;
        memcpy(words[wcount].w, current_word, cur_len);
        wcount++;
    }
    
    // Build a sorted list of distinct words with counts
    // Use a simple insertion sort approach since we have at most 5000 words
    // Store as: word (lowercase), count
    typedef struct { char w[10001]; size_t len; int count; } Entry;
    static Entry entries[wcount];
    for (int i = 0; i < wcount; i++) {
        entries[i].len = words[i].len;
        // Convert to lowercase
        for (size_t j = 0; j < words[i].len; j++) {
            entries[i].w[j] = tolower((unsigned char)words[i].w[j]);
        }
        entries[i].count = 1;
    }
    
    // Sort entries by word lexicographically using insertion sort
    for (int i = 1; i < wcount; i++) {
        Entry key = entries[i];
        int j = i - 1;
        while (j >= 0 && strcmp(entries[j].w, key.w) > 0) {
            entries[j + 1] = entries[j];
            j--;
        }
        entries[j + 1] = key;
    }
    
    // Now merge identical adjacent words
    int out_count = 0;
    if (wcount > 0) {
        for (int i = 0; i < wcount; i++) {
            if (i == 0 || strcmp(entries[i].w, entries[i-1].w) != 0) {
                // New distinct word
                out_count++;
                Entry *dest = &entries[out_count - 1];
                memcpy(dest->w, entries[i].w, entries[i].len);
                dest->len = entries[i].len;
                dest->count = 1;
            } else {
                // Same word, increment count
                entries[out_count - 1].count++;
            }
        }
    }
    
    // Output
    for (int i = 0; i < out_count; i++) {
        printf("%s %d\n", entries[i].w, entries[i].count);
    }
    
    return 0;
}
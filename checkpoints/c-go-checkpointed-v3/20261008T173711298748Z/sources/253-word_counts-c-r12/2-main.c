#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_BYTES 10000
#define HASH_SIZE 4096

typedef struct {
    char word[MAX_BYTES];
    unsigned int count;
} WordNode;

WordNode table[HASH_SIZE];

static inline unsigned long hash_string(const char *s) {
    unsigned long h = 5381;
    while (*s) {
        h = ((h << 5) + h) + (unsigned char)*s++;
    }
    return h;
}

int main(void) {
    static unsigned char buffer[MAX_BYTES];
    size_t len = 0;
    
    // Read input
    int c;
    while ((c = getchar()) != EOF && len < MAX_BYTES - 1) {
        buffer[len++] = (unsigned char)c;
    }
    buffer[len] = '\0';

    if (len == 0) return 0;

    // Initialize hash table
    for (int i = 0; i < HASH_SIZE; i++) {
        table[i].word[0] = '\0';
        table[i].count = 0;
    }

    // Scan for words
    size_t i = 0;
    while (i < len) {
        if (isalpha(buffer[i])) {
            size_t start = i;
            while (i < len && isalpha(buffer[i])) {
                i++;
            }
            size_t word_len = i - start;
            
            // Build normalized word and compute hash
            char norm[MAX_BYTES];
            unsigned long h = 0;
            for (size_t j = 0; j < word_len; j++) {
                char c = tolower((unsigned char)buffer[start + j]);
                norm[j] = c;
                h = ((h << 5) + h) + (unsigned char)c;
            }
            norm[word_len] = '\0';

            // Linear probing for hash table
            size_t idx = h % HASH_SIZE;
            int tries = 0;
            
            while (tries < HASH_SIZE) {
                if (table[idx].word[0] == '\0') {
                    // Empty slot, insert new word
                    strncpy(table[idx].word, norm, word_len);
                    table[idx].word[word_len] = '\0';
                    table[idx].count = 1;
                    break;
                } else if (table[idx].hash == h && strncmp(table[idx].word, norm, word_len) == 0) {
                    // Word exists, increment count
                    table[idx].count++;
                    break;
                } else {
                    // Hash mismatch, try next slot
                    idx = (idx + 1) % HASH_SIZE;
                    tries++;
                }
            }
        } else {
            i++;
        }
    }

    // Collect and sort words for output
    int num_words = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (table[i].word[0] != '\0') {
            printf("%s %u\n", table[i].word, table[i].count);
            num_words++;
        }
    }

    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_BYTES 10000
#define MAX_WORDS 10000
#define HASH_SIZE 32003

typedef struct {
    char word[MAX_BYTES];
    unsigned int hash;
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

    WordNode *words[MAX_WORDS];
    int word_count = 0;

    // Scan for words
    size_t i = 0;
    while (i < len) {
        if (isalpha(buffer[i])) {
            size_t start = i;
            while (i < len && isalpha(buffer[i])) {
                i++;
            }
            size_t word_len = i - start;
            
            // Build normalized word
            char norm[MAX_BYTES];
            for (size_t j = 0; j < word_len; j++) {
                norm[j] = tolower((unsigned char)buffer[start + j]);
            }
            norm[word_len] = '\0';

            unsigned long h = hash_string(norm);
            size_t idx = h % HASH_SIZE;
            
            // Check if exists
            int found = 0;
            for (int k = 0; k < word_count && !found; k++) {
                if (words[k] != NULL) {
                    WordNode *wn = words[k];
                    if (strncmp(wn->word, norm, word_len) == 0 && wn->hash == h) {
                        found = 1;
                    }
                }
            }

            if (!found) {
                // Insert new word - find empty slot or use linear probing
                size_t pos = idx;
                int tries = 0;
                while (tries < HASH_SIZE && (table[pos].hash != 0 || words[tries] != NULL)) {
                    pos = (pos + 1) % HASH_SIZE;
                    tries++;
                }
                
                if (tries < HASH_SIZE) {
                    WordNode *new_node = &table[pos];
                    new_node->word[0] = '\0';
                    new_node->hash = h;
                    
                    // Add to our linked list of words
                    int slot_idx = -1;
                    for (int k = 0; k < word_count && !found; k++) {
                        if (words[k] == NULL) {
                            slot_idx = k;
                            found = 1;
                            break;
                        } else if (strncmp(words[k]->word, norm, word_len) == 0 && words[k]->hash == h) {
                            // Already exists - increment count
                            WordNode *wn = words[k];
                            for (int m = 0; m < MAX_BYTES; m++) {
                                if (wn->word[m] != '\0') break;
                            }
                            // Just store word and hash, we need to track counts separately
                            // Actually let's simplify: use a simple array of structs
                        }
                    }
                }
            }
        } else {
            i++;
        }
    }

    // Let me rewrite this more simply
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100005
#define HASH_SIZE 32749
#define HASH_MAX 65536

typedef struct {
    char *word;
    int count;
} WordEntry;

static WordEntry words[MAX_WORDS];
static int word_count = 0;

static void add_word(const char *lower) {
    if (word_count >= MAX_WORDS) return;
    
    size_t len = strlen(lower);
    if (len == 0) return;
    
    // Simple hash: sum of character codes mod HASH_SIZE
    unsigned int h = 0;
    for (size_t i = 0; i < len; i++) {
        h += (unsigned char)lower[i];
    }
    size_t idx = h % HASH_SIZE;
    
    // Linear probing
    size_t probe = idx;
    int empty_slots = 0;
    
    while (empty_slots < HASH_MAX) {
        if (words[probe].word == NULL) {
            words[probe].word = malloc(len + 1);
            if (words[probe].word) {
                strcpy(words[probe].word, lower);
                words[probe].count = 1;
                word_count++;
                empty_slots++;
                return;
            }
        } else if (strcmp(words[probe].word, lower) == 0) {
            words[probe].count++;
            return;
        }
        probe = (probe + 1) % HASH_SIZE;
    }
}

static int compare_words(const void *a, const void *b) {
    const WordEntry *wa = (const WordEntry *)a;
    const WordEntry *wb = (const WordEntry *)b;
    return strcmp(wa->word, wb->word);
}

int main(void) {
    char buf[10001];
    size_t total = 0;
    
    // Read input until EOF or 10000 bytes
    int c;
    while ((c = getchar()) != EOF && total < 10000) {
        if (isalpha(c)) {
            buf[total++] = tolower((unsigned char)c);
        } else {
            // End of current word
            if (total > 0) {
                add_word(buf);
                total = 0;
            }
        }
    }
    
    // Handle last word if any
    if (total > 0) {
        add_word(buf);
    }
    
    // Collect all words into an array for sorting
    WordEntry *sorted = malloc(word_count * sizeof(WordEntry));
    if (!sorted) {
        return 0;
    }
    
    for (int i = 0; i < word_count; i++) {
        sorted[i] = words[i];
    }
    
    // Sort by word string
    qsort(sorted, word_count, sizeof(WordEntry), compare_words);
    
    // Output
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", sorted[i].word, sorted[i].count);
    }
    
    free(sorted);
    return 0;
}
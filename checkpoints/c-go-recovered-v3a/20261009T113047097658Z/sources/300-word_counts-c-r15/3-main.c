#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100005

typedef struct {
    char *word;
    int count;
} WordEntry;

static WordEntry words[MAX_WORDS];
static int word_count = 0;

static void add_word(const char *lower) {
    size_t len = strlen(lower);
    if (len == 0 || word_count >= MAX_WORDS) return;
    
    // Linear search - should be fast enough for small inputs
    for (int i = 0; i < word_count; i++) {
        if (strcmp(words[i].word, lower) == 0) {
            words[i].count++;
            return;
        }
    }
    
    // Add new word
    words[word_count].word = malloc(len + 1);
    if (words[word_count].word) {
        strcpy(words[word_count].word, lower);
        words[word_count].count = 1;
        word_count++;
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
    
    // Sort by word string
    qsort(words, word_count, sizeof(WordEntry), compare_words);
    
    // Output
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
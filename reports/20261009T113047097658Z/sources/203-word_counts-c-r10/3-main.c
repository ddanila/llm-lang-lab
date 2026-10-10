#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 20000
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry *)a)->word, ((WordEntry *)b)->word);
}

int main(void) {
    unsigned char buf[10000];
    size_t n = 0;
    int c;

    while ((c = getchar()) != EOF && n < sizeof(buf)) {
        buf[n++] = (unsigned char)c;
    }

    if (n == 0) {
        return 0;
    }

    WordEntry words[MAX_WORDS];
    int word_count = 0;

    size_t i = 0;
    while (i < n) {
        unsigned char ch = buf[i];
        if (isalpha(ch)) {
            // Start of a word, collect all letters
            char w[MAX_WORD_LEN];
            size_t wlen = 0;
            int j = (int)i;
            while (j < (int)n && isalpha(buf[j])) {
                w[wlen++] = buf[j++];
            }
            
            // Convert to lowercase
            for (size_t k = 0; k < wlen; k++) {
                w[k] = (char)tolower((unsigned char)w[k]);
            }

            // Check if word already exists
            int found = 0;
            for (int k = 0; k < word_count; k++) {
                if (strcmp(words[k].word, w) == 0) {
                    words[k].count++;
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (word_count >= MAX_WORDS) {
                    // Should not happen with given constraints
                    break;
                }
                strcpy(words[word_count].word, w);
                words[word_count].count = 1;
                word_count++;
            }

            i = j; // Skip past the word
        } else {
            i++;
        }
    }

    if (word_count == 0) {
        return 0;
    }

    qsort(words, word_count, sizeof(WordEntry), compare_words);

    for (int k = 0; k < word_count; k++) {
        printf("%s %d\n", words[k].word, words[k].count);
    }

    return 0;
}
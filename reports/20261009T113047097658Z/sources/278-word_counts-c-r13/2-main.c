#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BYTES 10000

typedef struct {
    char word[10005];
    int count;
} WordEntry;

static int compare_entries(const void *a, const void *b) {
    const WordEntry *ea = (const WordEntry *)a;
    const WordEntry *eb = (const WordEntry *)b;
    return strcmp(ea->word, eb->word);
}

int main(void) {
    unsigned char buf[MAX_BYTES];
    size_t n = 0;
    int c;

    while ((c = getchar()) != EOF && n < MAX_BYTES - 1) {
        buf[n++] = (unsigned char)c;
    }
    buf[n] = '\0';

    WordEntry *words = NULL;
    size_t word_count = 0;
    size_t capacity = 0;

    const unsigned char *p = buf;
    while (*p) {
        if (isalpha(*p)) {
            // Start of a word or continue existing
            if (word_count == capacity) {
                capacity = capacity ? capacity * 2 : 16;
                words = realloc(words, capacity * sizeof(WordEntry));
                if (!words) return 1;
            }

            size_t len = 0;
            while (*p && isalpha(*p)) {
                // Store lowercase
                words[word_count].word[len] = tolower(*p);
                len++;
                p++;
            }
            words[word_count].word[len] = '\0';

            // Check if word already exists (binary search)
            int lo = 0, hi = (int)word_count - 1;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                int cmp = strcmp(words[mid].word, words[word_count].word);
                if (cmp == 0) {
                    words[mid].count++;
                    break; // Found and merged
                } else if (cmp < 0) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }

            word_count++;
        } else {
            p++;
        }
    }

    // Sort words lexicographically
    qsort(words, word_count, sizeof(WordEntry), compare_entries);

    for (size_t i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    free(words);
    return 0;
}
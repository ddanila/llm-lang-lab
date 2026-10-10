#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 50000
#define MAX_WORD_LEN 10000

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int count;
} WordEntry;

static WordEntry words[MAX_WORDS];
static int word_count = 0;

int compare_words(const void *a, const void *b) {
    const WordEntry *wa = (const WordEntry *)a;
    const WordEntry *wb = (const WordEntry *)b;
    return strcmp(wa->word, wb->word);
}

int main(void) {
    char buf[MAX_WORD_LEN + 1];
    size_t len = 0;
    
    int c;
    while ((c = getchar()) != EOF && len < MAX_WORD_LEN) {
        unsigned char uc = (unsigned char)c;
        if (isalpha(uc)) {
            buf[len++] = tolower(uc);
        } else {
            // End of current word - treat CR, LF, and other non-alpha as separators
            if (len > 0) {
                // Check if this word already exists
                int found = 0;
                for (int i = 0; i < word_count; i++) {
                    if (strcmp(words[i].word, buf) == 0) {
                        words[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    if (word_count < MAX_WORDS) {
                        strcpy(words[word_count].word, buf);
                        words[word_count].count = 1;
                        word_count++;
                    }
                }
            }
            len = 0;
        }
    }
    
    // Handle last word if file ended with a letter
    if (len > 0) {
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i].word, buf) == 0) {
                words[i].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (word_count < MAX_WORDS) {
                strcpy(words[word_count].word, buf);
                words[word_count].count = 1;
                word_count++;
            }
        }
    }
    
    // Sort words lexicographically
    qsort(words, word_count, sizeof(WordEntry), compare_words);
    
    // Output results
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
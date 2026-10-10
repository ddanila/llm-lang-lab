#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 20000
#define MAX_WORD_LEN 10001

int main(void) {
    unsigned char buf[10000];
    size_t len = 0;
    int c;

    while ((c = getchar()) != EOF && len < 10000) {
        buf[len++] = (unsigned char)c;
    }

    struct Word {
        char word[MAX_WORD_LEN];
        int count;
    };
    static struct Word words[MAX_WORDS];
    int n_words = 0;

    for (size_t i = 0; i < len; ) {
        size_t start = i;
        while (i < len && isalpha(buf[i])) {
            i++;
        }
        if (i > start) {
            char lower[MAX_WORD_LEN];
            int j = 0;
            for (size_t k = start; k < i; k++) {
                lower[j++] = tolower((unsigned char)buf[k]);
            }
            lower[j] = '\0';

            int found = -1;
            for (int idx = 0; idx < n_words; idx++) {
                if (strcmp(words[idx].word, lower) == 0) {
                    found = idx;
                    break;
                }
            }

            if (found >= 0) {
                words[found].count++;
            } else {
                int insert_idx = n_words;
                for (int idx = 0; idx < n_words; idx++) {
                    if (strcmp(words[idx].word, lower) > 0) {
                        insert_idx = idx;
                        break;
                    }
                }

                memmove(&words[insert_idx + 1], &words[insert_idx], 
                       (n_words - insert_idx) * sizeof(struct Word));

                strcpy(words[insert_idx].word, lower);
                words[insert_idx].count = 1;
                n_words++;
            }
        }
    }

    for (int i = 0; i < n_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    return 0;
}
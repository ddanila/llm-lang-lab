#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    unsigned char buf[10000];
    size_t len = 0;
    int c;

    while ((c = getchar()) != EOF && len < 10000) {
        buf[len++] = (unsigned char)c;
    }
    buf[len] = '\0';

    typedef struct {
        char *word;
        int count;
    } Entry;

    Entry *words = NULL;
    size_t nwords = 0;

    for (size_t i = 0; i < len; ) {
        size_t j = i;
        while (j < len && isalpha(buf[j])) {
            j++;
        }
        if (j == i) {
            i++;
            continue;
        }

        size_t wlen = j - i;
        char *lower = malloc(wlen + 1);
        for (size_t k = 0; k < wlen; k++) {
            lower[k] = tolower((unsigned char)buf[i + k]);
        }
        lower[wlen] = '\0';

        int found = 0;
        for (size_t k = 0; k < nwords; k++) {
            if (strcmp(words[k].word, lower) == 0) {
                words[k].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            Entry *neww = malloc(sizeof(Entry));
            neww->word = malloc(wlen + 1);
            for (size_t k = 0; k < wlen; k++) {
                neww->word[k] = lower[k];
            }
            neww->word[wlen] = '\0';
            neww->count = 1;

            // Find position to insert (maintain sorted order)
            size_t pos = nwords;
            for (size_t k = 0; k < nwords; k++) {
                if (strcmp(words[k].word, lower) > 0) {
                    pos = k + 1;
                    break;
                }
            }

            // Insert at position pos
            if (pos > 0 && pos <= nwords) {
                memmove(&words[pos], &words[pos - 1], (nwords - pos + 1) * sizeof(Entry));
            } else if (pos == 0) {
                memmove(&words[1], words, nwords * sizeof(Entry));
            }

            words[pos - 1] = *neww;
            nwords++;

            free(lower);
        } else {
            free(lower);
        }

        i = j;
    }

    for (size_t k = 0; k < nwords; k++) {
        printf("%s %d\n", words[k].word, words[k].count);
        free(words[k].word);
    }

    free(words);

    return 0;
}
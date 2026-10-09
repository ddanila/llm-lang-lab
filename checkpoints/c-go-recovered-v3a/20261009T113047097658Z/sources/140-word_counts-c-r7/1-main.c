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

    // Count words
    struct Word {
        char word[10001];
        int count;
    };
    static struct Word words[20000];
    int n_words = 0;

    for (size_t i = 0; i < len; ) {
        size_t start = i;
        while (i < len && isalpha(buf[i])) {
            i++;
        }
        if (i > start) {
            // Extract word
            char lower[10001];
            int j = 0;
            for (size_t k = start; k < i; k++) {
                lower[j++] = tolower(buf[k]);
            }
            lower[j] = '\0';

            // Check if word exists
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
                // Insert in sorted order
                int insert_idx = n_words;
                for (int idx = 0; idx < n_words; idx++) {
                    if (strcmp(words[idx].word, lower) > 0) {
                        insert_idx = idx;
                        break;
                    }
                }

                // Shift
                memmove(&words[insert_idx + 1], &words[insert_idx], 
                       (n_words - insert_idx) * sizeof(struct Word));

                strcpy(words[insert_idx].word, lower);
                words[insert_idx].count = 1;
                n_words++;
            }
        }
    }

    // Output
    for (int i = 0; i < n_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    return 0;
}
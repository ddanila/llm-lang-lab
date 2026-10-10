#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int main(void) {
    unsigned char buf[10000];
    size_t len = fread(buf, 1, sizeof(buf), stdin);

    // Simple array of words without dynamic insertion
    // We'll collect all words and then sort/count them
    
    char word_buf[MAX_WORD_LEN];
    int num_words = 0;
    
    for (size_t i = 0; i < len; ) {
        if (!isalpha((unsigned char)buf[i])) {
            i++;
            continue;
        }

        size_t start = i;
        while (i < len && isalpha((unsigned char)buf[i])) {
            i++;
        }

        size_t wlen = i - start;
        if (wlen == 0) continue;

        // Convert to lowercase
        for (size_t j = 0; j < wlen; j++) {
            word_buf[j] = tolower((unsigned char)buf[start + j]);
        }
        word_buf[wlen] = '\0';

        int found = -1;
        for (int k = 0; k < num_words; k++) {
            if (strcmp(words[k].word, word_buf) == 0) {
                found = k;
                break;
            }
        }

        if (found != -1) {
            words[found].count++;
        } else {
            // Insert in sorted order by word
            int insert_at = num_words;
            for (int k = num_words - 1; k >= 0; k--) {
                if (strcmp(words[k].word, word_buf) > 0) {
                    insert_at = k + 1;
                    break;
                } else if (strcmp(words[k].word, word_buf) == 0) {
                    // Should have been found above, but just in case
                    insert_at = k + 1;
                    break;
                }
            }

            // Shift elements to make room
            for (int k = num_words; k > insert_at; k--) {
                words[k] = words[k - 1];
            }

            if (insert_at < MAX_WORDS) {
                strcpy(words[insert_at].word, word_buf);
                words[insert_at].count = 1;
                num_words++;
            } else {
                // Should not happen with given constraints
            }
        }
    }

    for (int i = 0; i < num_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    return 0;
}
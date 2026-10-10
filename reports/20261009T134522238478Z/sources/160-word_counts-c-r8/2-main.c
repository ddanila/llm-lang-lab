#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

static int compare_entries(const void *a, const void *b) {
    return strcmp(((WordEntry*)a)->word, ((WordEntry*)b)->word);
}

int main(void) {
    unsigned char buf[10005];
    size_t len = 0;
    int c;

    while ((c = getchar()) != EOF && len < sizeof(buf)) {
        buf[len++] = (unsigned char)c;
    }
    buf[len] = '\0';

    WordEntry words[MAX_WORDS];
    int word_count = 0;

    const unsigned char *p = buf;
    while (*p) {
        if (isalpha(*p)) {
            char start_word[MAX_WORD_LEN];
            size_t i = 0;
            while (i < MAX_WORD_LEN - 1 && isalpha(p[i])) {
                start_word[i] = tolower(p[i]);
                p++;
                i++;
            }
            start_word[i] = '\0';

            int found = 0;
            for (int j = 0; j < word_count; j++) {
                if (strcmp(words[j].word, start_word) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }

            if (!found && word_count < MAX_WORDS) {
                strncpy(words[word_count].word, start_word, MAX_WORD_LEN - 1);
                words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                words[word_count].count = 1;
                word_count++;
            }
        } else if (*p == ' ') {
            p++;
        } else {
            p++;
        }
    }

    qsort(words, word_count, sizeof(WordEntry), compare_entries);

    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    return 0;
}
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

int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry*)a)->word, ((WordEntry*)b)->word);
}

int main(void) {
    unsigned char buf[10001];
    size_t len = 0;
    
    while (len < sizeof(buf)) {
        int c = getchar();
        if (c == EOF) break;
        buf[len++] = (unsigned char)c;
    }

    WordEntry words[MAX_WORDS];
    int word_count = 0;
    int current_word_start = -1;
    char current_word[MAX_WORD_LEN] = {0};
    size_t current_word_len = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            if (current_word_start == -1) {
                current_word_start = word_count;
                current_word[current_word_len++] = tolower(c);
            } else {
                current_word[current_word_len++] = tolower(c);
            }
            current_word[current_word_len] = '\0';
        } else {
            if (current_word_start != -1) {
                strcpy(words[word_count].word, current_word);
                words[word_count].count = 1;
                word_count++;
                current_word_start = -1;
                current_word_len = 0;
            }
        }
    }

    if (current_word_start != -1) {
        strcpy(words[word_count].word, current_word);
        words[word_count].count = 1;
        word_count++;
    }

    if (word_count > 0) {
        qsort(words, word_count, sizeof(WordEntry), compare_words);

        for (int i = 0; i < word_count; i++) {
            printf("%s %d\n", words[i].word, words[i].count);
        }
    }

    return 0;
}
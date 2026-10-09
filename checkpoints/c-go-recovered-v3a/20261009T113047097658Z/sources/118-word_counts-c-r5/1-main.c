#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 65536
#define MAX_WORD_LEN 10001

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

static WordEntry words[MAX_WORDS];
static int word_count = 0;

int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry*)a)->word, ((WordEntry*)b)->word);
}

void add_word(const char *w) {
    for (int i = 0; i < word_count; i++) {
        if (strcmp(words[i].word, w) == 0) {
            words[i].count++;
            return;
        }
    }
    if (word_count < MAX_WORDS) {
        strcpy(words[word_count].word, w);
        words[word_count].count = 1;
        word_count++;
    }
}

int main(void) {
    unsigned char buf[10001];
    size_t len = 0;
    int c;
    
    while ((c = getchar()) != EOF && len < 10000) {
        buf[len++] = (unsigned char)c;
    }
    buf[len] = '\0';
    
    const char *p = buf;
    char current_word[MAX_WORD_LEN];
    size_t word_len = 0;
    
    while (*p) {
        if (isalpha((unsigned char)*p)) {
            current_word[word_len++] = tolower((unsigned char)*p);
            p++;
        } else {
            if (word_len > 0) {
                current_word[word_len] = '\0';
                add_word(current_word);
                word_len = 0;
            }
            while (*p && !isalpha((unsigned char)*p)) {
                p++;
            }
        }
    }
    
    if (word_len > 0) {
        current_word[word_len] = '\0';
        add_word(current_word);
    }
    
    qsort(words, word_count, sizeof(WordEntry), compare_words);
    
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
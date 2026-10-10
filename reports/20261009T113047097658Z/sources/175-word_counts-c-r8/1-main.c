#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 65536
#define MAX_WORD_LEN 10001

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

WordEntry words[MAX_WORDS];
int word_count = 0;

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

int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry*)a)->word, ((WordEntry*)b)->word);
}

int main(void) {
    unsigned char buf[10001];
    size_t len = 0;
    int c;
    
    while ((c = getchar()) != EOF && len < 10000) {
        buf[len++] = (unsigned char)c;
    }
    
    if (len == 0) return 0;
    
    int in_word = 0;
    char current_word[MAX_WORD_LEN] = {0};
    int word_len = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char ch = buf[i];
        
        if (isalpha(ch)) {
            if (!in_word) {
                in_word = 1;
                word_len = 0;
            }
            current_word[word_len++] = tolower((unsigned char)ch);
            if (word_len < MAX_WORD_LEN - 1) {
                current_word[word_len] = '\0';
            }
        } else {
            if (in_word) {
                add_word(current_word);
                in_word = 0;
                word_len = 0;
            }
        }
    }
    
    // Handle last word if input ends with letters
    if (in_word && word_len > 0) {
        current_word[word_len] = '\0';
        add_word(current_word);
    }
    
    if (word_count == 0) return 0;
    
    qsort(words, word_count, sizeof(WordEntry), compare_words);
    
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
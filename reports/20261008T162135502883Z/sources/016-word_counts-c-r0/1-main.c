#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 26000
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int main(void) {
    unsigned char buf[10000];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    
    if (len == 0) return 0;
    
    // Find all word boundaries and collect words
    int n_words = 0;
    WordEntry words[MAX_WORDS];
    char current_word[MAX_WORD_LEN];
    size_t cur_len = 0;
    int in_word = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            if (!in_word) {
                // Start a new word
                current_word[cur_len++] = tolower(c);
                in_word = 1;
            } else {
                current_word[cur_len++] = tolower(c);
            }
        } else {
            if (in_word) {
                // End of word, store it
                words[n_words].count = 0;
                strncpy(words[n_words].word, current_word, MAX_WORD_LEN - 1);
                words[n_words].word[MAX_WORD_LEN - 1] = '\0';
                n_words++;
                cur_len = 0;
                in_word = 0;
            }
        }
    }
    
    // Handle last word if input ends with a letter
    if (in_word && cur_len > 0) {
        words[n_words].count = 0;
        strncpy(words[n_words].word, current_word, MAX_WORD_LEN - 1);
        words[n_words].word[MAX_WORD_LEN - 1] = '\0';
        n_words++;
    }
    
    if (n_words == 0) return 0;
    
    // Sort by ASCII order of word string
    for (int i = 0; i < n_words - 1; i++) {
        for (int j = 0; j < n_words - 1 - i; j++) {
            if (strcmp(words[j].word, words[j + 1].word) > 0) {
                WordEntry tmp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tmp;
            }
        }
    }
    
    // Output results
    for (int i = 0; i < n_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
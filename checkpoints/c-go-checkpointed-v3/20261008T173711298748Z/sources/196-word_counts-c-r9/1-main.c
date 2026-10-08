#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

static WordEntry words[MAX_WORDS];
static int num_words = 0;

int find_or_add_word(const char *w) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, w) == 0) {
            words[i].count++;
            return 0;
        }
    }
    if (num_words >= MAX_WORDS) return -1;
    strncpy(words[num_words].word, w, MAX_WORD_LEN - 1);
    words[num_words].word[MAX_WORD_LEN - 1] = '\0';
    words[num_words].count = 1;
    num_words++;
    return 0;
}

int main(void) {
    char buf[10005];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    
    int state = 0; // 0: accumulating word, 1: non-letter (skip)
    char current_word[MAX_WORD_LEN] = {0};
    size_t cur_len = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)buf[i];
        
        if (isalpha(c)) {
            if (state == 1) {
                // Start of new word
                cur_len = 0;
                current_word[cur_len++] = tolower((unsigned char)c);
                state = 0;
            } else {
                if (cur_len < MAX_WORD_LEN - 1) {
                    current_word[cur_len++] = tolower((unsigned char)c);
                }
            }
        } else {
            if (state == 0 && cur_len > 0) {
                // End of word
                find_or_add_word(current_word);
                cur_len = 0;
                current_word[0] = '\0';
            }
            state = 1;
        }
    }
    
    if (state == 0 && cur_len > 0) {
        find_or_add_word(current_word);
    }
    
    // Sort words lexicographically
    for (int i = 0; i < num_words - 1; i++) {
        for (int j = i + 1; j < num_words; j++) {
            if (strcmp(words[i].word, words[j].word) > 0) {
                WordEntry tmp = words[i];
                words[i] = words[j];
                words[j] = tmp;
            }
        }
    }
    
    for (int i = 0; i < num_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
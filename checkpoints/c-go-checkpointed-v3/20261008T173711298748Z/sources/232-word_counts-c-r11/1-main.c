#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 65536
#define MAX_WORD_LEN 10000

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int count;
} WordCount;

static WordCount words[MAX_WORDS];
static int num_words = 0;

int find_word(const char *word, int len) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0 && words[i].count > 0) {
            return i;
        }
    }
    return -1;
}

void add_word(const char *word, int len) {
    int idx = find_word(word, len);
    if (idx != -1) {
        words[idx].count++;
    } else {
        strcpy(words[num_words].word, word);
        words[num_words].count = 1;
        num_words++;
    }
}

int main(void) {
    char buffer[10000];
    int len = 0;
    
    while (len < (int)sizeof(buffer) && getchar() != EOF) {
        buffer[len++] = getchar();
    }
    
    if (len == 0) return 0;
    
    char current_word[MAX_WORD_LEN + 1] = "";
    int current_len = 0;
    
    for (int i = 0; i < len; i++) {
        unsigned char c = buffer[i];
        
        if (isalpha(c)) {
            if (current_len == MAX_WORD_LEN) break;
            current_word[current_len++] = tolower(c);
        } else {
            if (current_len > 0) {
                add_word(current_word, current_len);
                current_word[0] = '\0';
                current_len = 0;
            }
        }
    }
    
    if (current_len > 0) {
        add_word(current_word, current_len);
    }
    
    // Sort words lexicographically
    for (int i = 0; i < num_words - 1; i++) {
        for (int j = i + 1; j < num_words; j++) {
            if (strcmp(words[i].word, words[j].word) > 0) {
                WordCount temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < num_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
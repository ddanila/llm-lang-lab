#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int compare_entries(const void *a, const void *b) {
    return strcmp(((WordEntry*)a)->word, ((WordEntry*)b)->word);
}

int main(void) {
    unsigned char buffer[10005];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    WordEntry words[MAX_WORDS];
    int num_words = 0;
    
    for (size_t i = 0; i < len; ) {
        if (!isalpha((unsigned char)buffer[i])) {
            i++;
            continue;
        }
        
        size_t start = i;
        while (i < len && isalpha((unsigned char)buffer[i])) {
            i++;
        }
        
        size_t word_len = i - start;
        if (word_len == 0) continue;
        
        char lower_word[MAX_WORD_LEN];
        for (size_t j = 0; j < word_len; j++) {
            lower_word[j] = tolower((unsigned char)buffer[start + j]);
        }
        lower_word[word_len] = '\0';
        
        int found = 0;
        for (int k = 0; k < num_words; k++) {
            if (strcmp(words[k].word, lower_word) == 0) {
                words[k].count++;
                found = 1;
                break;
            }
        }
        
        if (!found && num_words < MAX_WORDS) {
            strncpy(words[num_words].word, lower_word, MAX_WORD_LEN - 1);
            words[num_words].word[MAX_WORD_LEN - 1] = '\0';
            words[num_words].count = 1;
            num_words++;
        }
    }
    
    if (num_words == 0) {
        return 0;
    }
    
    qsort(words, num_words, sizeof(WordEntry), compare_entries);
    
    for (int k = 0; k < num_words; k++) {
        printf("%s %d\n", words[k].word, words[k].count);
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

// Compare function for qsort
int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry *)a)->word, ((WordEntry *)b)->word);
}

int main(void) {
    char buffer[10001];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    WordEntry words[MAX_WORDS];
    int word_count = 0;
    
    // Process input byte by byte
    int in_word = 0;
    char current_word[MAX_WORD_LEN] = {0};
    size_t current_len = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = buffer[i];
        
        if (isalpha(c)) {
            if (!in_word) {
                in_word = 1;
                current_len = 0;
                // Convert to lowercase immediately
                current_word[current_len++] = tolower(c);
            } else {
                if (current_len < MAX_WORD_LEN - 1) {
                    current_word[current_len++] = tolower(c);
                }
            }
        } else {
            if (in_word) {
                // End of word, store it
                int found = 0;
                for (int j = 0; j < word_count; j++) {
                    if (strcmp(words[j].word, current_word) == 0) {
                        words[j].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found && word_count < MAX_WORDS) {
                    strncpy(words[word_count].word, current_word, MAX_WORD_LEN - 1);
                    words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                    words[word_count].count = 1;
                    word_count++;
                }
                
                // Reset for next word
                in_word = 0;
                current_word[0] = '\0';
                current_len = 0;
            }
        }
    }
    
    // Handle last word if input ends with a letter
    if (in_word && current_len > 0) {
        int found = 0;
        for (int j = 0; j < word_count; j++) {
            if (strcmp(words[j].word, current_word) == 0) {
                words[j].count++;
                found = 1;
                break;
            }
        }
        if (!found && word_count < MAX_WORDS) {
            strncpy(words[word_count].word, current_word, MAX_WORD_LEN - 1);
            words[word_count].word[MAX_WORD_LEN - 1] = '\0';
            words[word_count].count = 1;
            word_count++;
        }
    }
    
    // Sort words lexicographically
    if (word_count > 0) {
        qsort(words, word_count, sizeof(WordEntry), compare_words);
    }
    
    // Output results
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
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

int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry *)a)->word, ((WordEntry *)b)->word);
}

int main(void) {
    signed char c;
    WordEntry words[MAX_WORDS];
    int word_count = 0;
    
    // Read character by character
    while ((c = getchar()) != EOF) {
        if (isalpha((unsigned char)c)) {
            if (word_count == 0) {
                // Start of first word
                char current_word[MAX_WORD_LEN];
                int current_len = 0;
                current_word[current_len++] = tolower((unsigned char)c);
                
                // Continue reading the word
                while ((c = getchar()) != EOF && isalpha((unsigned char)c)) {
                    if (current_len < MAX_WORD_LEN - 1) {
                        current_word[current_len++] = tolower((unsigned char)c);
                    }
                }
                
                // Store the completed word
                strncpy(words[word_count].word, current_word, MAX_WORD_LEN - 1);
                words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                words[word_count].count = 1;
                word_count++;
            } else {
                // Continue reading the current word (already stored)
                char current_word[MAX_WORD_LEN];
                int current_len = 0;
                while ((c = getchar()) != EOF && isalpha((unsigned char)c)) {
                    if (current_len < MAX_WORD_LEN - 1) {
                        current_word[current_len++] = tolower((unsigned char)c);
                    }
                }
                
                // Store the completed word
                strncpy(words[word_count].word, current_word, MAX_WORD_LEN - 1);
                words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                words[word_count].count++;
            }
        } else {
            // Non-letter character encountered - check if we have a pending word
            if (word_count > 0) {
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
                current_word[0] = '\0';
            }
        }
    }
    
    return 0;
}
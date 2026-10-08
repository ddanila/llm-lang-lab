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
    unsigned char c;
    WordEntry words[MAX_WORDS];
    int word_count = 0;
    
    // Read character by character
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            if (word_count == 0) {
                // Start of first word
                char current_word[MAX_WORD_LEN];
                int current_len = 0;
                current_word[current_len++] = tolower((unsigned char)c);
                
                // Continue reading the word
                while ((c = getchar()) != EOF && isalpha(c)) {
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
                while ((c = getchar()) != EOF && isalpha(c)) {
                    if (current_len < MAX_WORD_LEN - 1) {
                        current_word[current_len++] = tolower((unsigned char)c);
                    }
                }
                
                // Check if we got more letters (non-EOF case)
                while (isalpha(c)) {
                    c = getchar();
                    if (!isalpha(c)) break;
                    if (word_count > 0 && current_len < MAX_WORD_LEN - 1) {
                        current_word[current_len++] = tolower((unsigned char)c);
                    }
                }
                
                // Store the completed word
                strncpy(words[word_count].word, current_word, MAX_WORD_LEN - 1);
                words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                words[word_count].count++;
            }
        } else {
            // Non-letter character encountered
            break;
        }
    }
    
    return 0;
}
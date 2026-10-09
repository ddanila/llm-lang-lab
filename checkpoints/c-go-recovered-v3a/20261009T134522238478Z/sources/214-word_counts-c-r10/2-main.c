#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_LEN 200

typedef struct {
    char word[MAX_LEN];
    int count;
} WordCount;

int compare_words(const void *a, const void *b) {
    return strcmp(((WordCount *)a)->word, ((WordCount *)b)->word);
}

int main(void) {
    unsigned char buf[10000];
    size_t len = 0;
    int c;
    WordCount words[MAX_WORDS];
    int word_count = 0;
    char current_word[MAX_LEN];
    size_t current_len = 0;

    while ((c = getchar()) != EOF) {
        if (isascii(c) && isalpha(c)) {
            current_word[current_len++] = (unsigned char)tolower(c);
            if (current_len >= MAX_LEN - 1) break; // Word too long
        } else {
            if (current_len > 0) {
                // Store the word
                strncpy(current_word, current_word, MAX_LEN - 1);
                current_word[MAX_LEN - 1] = '\0';
                
                // Check if word already exists
                int found = 0;
                for (int i = 0; i < word_count; i++) {
                    if (strcmp(words[i].word, current_word) == 0) {
                        words[i].count++;
                        found = 1;
                        break;
                    }
                }
                
                if (!found && word_count < MAX_WORDS) {
                    strncpy(words[word_count].word, current_word, MAX_LEN - 1);
                    words[word_count].word[MAX_LEN - 1] = '\0';
                    words[word_count].count = 1;
                    word_count++;
                }
                
                current_len = 0;
            }
        }
    }

    // Handle last word if exists
    if (current_len > 0) {
        strncpy(current_word, current_word, MAX_LEN - 1);
        current_word[MAX_LEN - 1] = '\0';
        
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i].word, current_word) == 0) {
                words[i].count++;
                found = 1;
                break;
            }
        }
        
        if (!found && word_count < MAX_WORDS) {
            strncpy(words[word_count].word, current_word, MAX_LEN - 1);
            words[word_count].word[MAX_LEN - 1] = '\0';
            words[word_count].count = 1;
            word_count++;
        }
    }

    // Sort words lexicographically
    for (int i = 0; i < word_count - 1; i++) {
        for (int j = i + 1; j < word_count; j++) {
            if (strcmp(words[i].word, words[j].word) > 0) {
                WordCount temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
    }

    // Output results
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    return 0;
}
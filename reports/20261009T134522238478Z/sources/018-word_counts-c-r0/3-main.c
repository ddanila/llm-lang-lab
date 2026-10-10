#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} Word;

int main(void) {
    char buffer[10001];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    if (len == 0) return 0;
    
    // First pass: collect all words
    Word *words = malloc(sizeof(Word) * MAX_WORDS);
    if (!words) return 0;
    
    int word_count = 0;
    char current_word[MAX_WORD_LEN] = {0};
    int in_word = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = buffer[i];
        
        if (isalpha(c)) {
            // Continue building word
            current_word[strlen(current_word)] = tolower(c);
        } else {
            if (in_word) {
                // End of word - store it
                int len_cur = strlen(current_word);
                if (len_cur > 0) {
                    Word *w = words;
                    int j = 0;
                    while (j < word_count && strcmp(w[j].word, current_word) < 0) {
                        w++;
                        j++;
                    }
                    
                    // Check if word already exists at position j
                    if (j < word_count && strcmp(w[j].word, current_word) == 0) {
                        w[j].count++;
                    } else {
                        memmove(&words[j+1], &words[j], sizeof(Word) * (word_count - j));
                        strcpy(words[j].word, current_word);
                        words[j].count = 1;
                        word_count++;
                    }
                }
                // Reset current word
                current_word[0] = '\0';
            }
        }
    }
    
    // Handle last word if exists
    if (strlen(current_word) > 0) {
        Word *w = words;
        int j = 0;
        while (j < word_count && strcmp(w[j].word, current_word) < 0) {
            w++;
            j++;
        }
        
        // Check if word already exists at position j
        if (j < word_count && strcmp(w[j].word, current_word) == 0) {
            w[j].count++;
        } else {
            memmove(&words[j+1], &words[j], sizeof(Word) * (word_count - j));
            strcpy(words[j].word, current_word);
            words[j].count = 1;
            word_count++;
        }
    }
    
    // Output sorted words
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    free(words);
    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 100005
#define MAX_WORD_LEN 10005

int main(void) {
    char buffer[10001];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    // Build a list of words and their counts
    struct Word {
        char word[MAX_WORD_LEN];
        int count;
    };
    struct Word words[MAX_WORDS];
    int word_count = 0;
    
    char current_word[10005] = {0};
    int in_word = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = buffer[i];
        
        if (isalpha(c)) {
            if (!in_word) {
                // Start new word
                strcpy(current_word, "");
                in_word = 1;
            }
            current_word[strlen(current_word)] = tolower(c);
        } else {
            if (in_word) {
                // End of word
                int len_cur = strlen(current_word);
                for (int j = 0; j < word_count; j++) {
                    if (strcmp(words[j].word, current_word) == 0) {
                        words[j].count++;
                        break;
                    } else if (words[j].count > 0 && 
                               strcmp(words[j].word, current_word) > 0) {
                        // Insert before to keep sorted order
                        memmove(&words[j+1], &words[j], sizeof(Word));
                        words[j] = (struct Word){current_word, 1};
                        word_count++;
                        break;
                    } else if (j == word_count - 1) {
                        // Append to end
                        strcpy(words[word_count].word, current_word);
                        words[word_count].count = 1;
                        word_count++;
                        break;
                    }
                }
                if (in_word && strcmp(current_word, "") == 0) {
                    // Word was empty or not added properly
                }
                in_word = 0;
            }
        }
    }
    
    // Handle last word if exists
    if (in_word) {
        int len_cur = strlen(current_word);
        for (int j = 0; j < word_count; j++) {
            if (strcmp(words[j].word, current_word) == 0) {
                words[j].count++;
                break;
            } else if (words[j].count > 0 && 
                       strcmp(words[j].word, current_word) > 0) {
                memmove(&words[j+1], &words[j], sizeof(Word));
                words[j] = (struct Word){current_word, 1};
                word_count++;
                break;
            } else if (j == word_count - 1) {
                strcpy(words[word_count].word, current_word);
                words[word_count].count = 1;
                word_count++;
                break;
            }
        }
    }
    
    // Output sorted words
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
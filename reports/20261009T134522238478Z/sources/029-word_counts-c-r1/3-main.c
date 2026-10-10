#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 10000

typedef struct {
    char word[MAX_LEN + 1];
    int count;
} WordEntry;

int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry *)a)->word, ((WordEntry *)b)->word);
}

int main(void) {
    char buffer[MAX_LEN + 1] = {0};
    size_t total_len = 0;
    int c;
    
    // Read input character by character until EOF or max length reached
    while ((c = getchar()) != EOF && total_len < MAX_LEN) {
        if (isalpha(c)) {
            buffer[total_len++] = islower(c) ? tolower(c) : c;
        } else {
            buffer[total_len] = '\0';
            
            if (total_len > 0) {
                WordEntry *words = malloc((MAX_LEN / 2 + 1) * sizeof(WordEntry));
                if (!words) {
                    return 1;
                }
                
                int num_words = 0;
                
                // First pass: count all words
                for (size_t i = 0; i < total_len; ) {
                    size_t start = i;
                    while (i < total_len && isalpha(buffer[i])) {
                        i++;
                    }
                    size_t len = i - start;
                    
                    // Find if word already exists
                    int found = 0;
                    for (int j = 0; j < num_words; j++) {
                        if (strcmp(words[j].word, buffer + start) == 0) {
                            words[j].count++;
                            found = 1;
                            break;
                        }
                    }
                    
                    if (!found && num_words < (MAX_LEN / 2 + 1)) {
                        strncpy(words[num_words].word, buffer + start, len);
                        words[num_words].word[len] = '\0';
                        words[num_words].count = 1;
                        num_words++;
                    }
                }
                
                // Sort by word (ascending ASCII order)
                qsort(words, num_words, sizeof(WordEntry), compare_words);
                
                // Output results
                for (int j = 0; j < num_words; j++) {
                    printf("%s %d\n", words[j].word, words[j].count);
                }
                
                free(words);
            }
            
            // Reset buffer for next word
            total_len = 0;
        }
    }
    
    // Handle last word if file ends with a letter (no trailing separator)
    if (total_len > 0) {
        WordEntry *words = malloc((MAX_LEN / 2 + 1) * sizeof(WordEntry));
        if (!words) {
            return 1;
        }
        
        int num_words = 0;
        
        // First pass: count all words
        for (size_t i = 0; i < total_len; ) {
            size_t start = i;
            while (i < total_len && isalpha(buffer[i])) {
                i++;
            }
            size_t len = i - start;
            
            // Find if word already exists
            int found = 0;
            for (int j = 0; j < num_words; j++) {
                if (strcmp(words[j].word, buffer + start) == 0) {
                    words[j].count++;
                    found = 1;
                    break;
                }
            }
            
            if (!found && num_words < (MAX_LEN / 2 + 1)) {
                strncpy(words[num_words].word, buffer + start, len);
                words[num_words].word[len] = '\0';
                words[num_words].count = 1;
                num_words++;
            }
        }
        
        // Sort by word (ascending ASCII order)
        qsort(words, num_words, sizeof(WordEntry), compare_words);
        
        // Output results
        for (int j = 0; j < num_words; j++) {
            printf("%s %d\n", words[j].word, words[j].count);
        }
        
        free(words);
    }
    
    return 0;
}
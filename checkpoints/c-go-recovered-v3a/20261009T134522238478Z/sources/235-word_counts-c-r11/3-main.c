#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

int main(void) {
    char buffer[10005];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    // Store words dynamically
    char **words = NULL;
    int word_count = 0;
    char current_word[MAX_WORD_LEN];
    size_t cur_len = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = buffer[i];
        if (isalpha(c)) {
            // lowercase it
            current_word[cur_len++] = tolower((unsigned char)c);
        } else {
            if (cur_len > 0) {
                words = realloc(words, (word_count + 1) * sizeof(char*));
                char *new_word = malloc(cur_len + 1);
                memcpy(new_word, current_word, cur_len);
                new_word[cur_len] = '\0';
                words[word_count++] = new_word;
                cur_len = 0;
            }
        }
    }
    
    // Handle last word if any
    if (cur_len > 0) {
        words = realloc(words, (word_count + 1) * sizeof(char*));
        char *new_word = malloc(cur_len + 1);
        memcpy(new_word, current_word, cur_len);
        new_word[cur_len] = '\0';
        words[word_count++] = new_word;
    }
    
    if (word_count == 0) {
        return 0;
    }
    
    // Insertion sort to get lexicographic order
    for (int i = 1; i < word_count; i++) {
        char *temp = words[i];
        int j = i - 1;
        while (j >= 0 && strcmp(words[j], temp) > 0) {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = temp;
    }
    
    // Now count consecutive duplicates and output
    char *prev = words[0];
    int count = 1;
    for (int i = 1; i < word_count; i++) {
        if (strcmp(words[i], prev) == 0) {
            count++;
        } else {
            printf("%s %d\n", prev, count);
            prev = words[i];
            count = 1;
        }
    }
    // Output last word
    printf("%s %d\n", prev, count);
    
    return 0;
}
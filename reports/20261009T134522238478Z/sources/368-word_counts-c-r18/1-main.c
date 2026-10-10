#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 50000
#define MAX_WORD_LEN 10000

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int count;
} WordEntry;

WordEntry words[MAX_WORDS];
int num_words = 0;

int find_or_add(const char *word) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    if (num_words >= MAX_WORDS) return -1;
    
    strcpy(words[num_words].word, word);
    words[num_words].count = 1;
    return num_words++;
}

int main(void) {
    char buffer[10005];
    int len = 0;
    
    // Read input until EOF or buffer full
    while (len < (int)sizeof(buffer) - 1 && scanf("%c", &buffer[len]) != EOF) {
        if (buffer[len] == '\n' || buffer[len] == '\r') {
            buffer[len] = ' ';
        }
        len++;
    }
    buffer[len] = '\0';
    
    int word_start = -1;
    int current_word_len = 0;
    
    for (int i = 0; buffer[i] != '\0'; i++) {
        char c = buffer[i];
        
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            if (word_start == -1) {
                word_start = i;
                current_word_len = 0;
            }
            current_word_len++;
        } else {
            if (word_start != -1 && current_word_len > 0) {
                // Process the word
                char lower[MAX_WORD_LEN + 1];
                for (int j = 0; j < current_word_len; j++) {
                    lower[j] = tolower((unsigned char)(buffer[word_start + j]));
                }
                lower[current_word_len] = '\0';
                
                int idx = find_or_add(lower);
                if (idx != -1) {
                    words[idx].count++;
                }
                
                word_start = -1;
                current_word_len = 0;
            }
        }
    }
    
    // Handle last word if file doesn't end with separator
    if (word_start != -1 && current_word_len > 0) {
        char lower[MAX_WORD_LEN + 1];
        for (int j = 0; j < current_word_len; j++) {
            lower[j] = tolower((unsigned char)(buffer[word_start + j]));
        }
        lower[current_word_len] = '\0';
        
        int idx = find_or_add(lower);
        if (idx != -1) {
            words[idx].count++;
        }
    }
    
    // Sort words by ASCII order using simple insertion sort
    for (int i = 1; i < num_words; i++) {
        WordEntry key = words[i];
        int j = i - 1;
        
        while (j >= 0 && strcmp(words[j].word, key.word) > 0) {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = key;
    }
    
    // Output results
    for (int i = 0; i < num_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
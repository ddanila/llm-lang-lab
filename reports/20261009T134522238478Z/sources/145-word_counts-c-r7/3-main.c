#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 262144
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int main(void) {
    static char buffer[10001];
    static WordEntry words[MAX_WORDS];
    static int word_count = 0;
    
    size_t n = fread(buffer, 1, sizeof(buffer), stdin);
    
    if (n == 0) return 0;
    
    const char *p = buffer;
    size_t i = 0;
    while (i < n) {
        if (!isalpha((unsigned char)p[i])) {
            i++;
            continue;
        }
        
        // Start of a word
        size_t start = i;
        while (i < n && isalpha((unsigned char)p[i])) {
            i++;
        }
        
        // Convert to lowercase and store
        size_t len = i - start;
        for (size_t j = 0; j < len; j++) {
            words[word_count].word[j] = p[start + j];
            words[word_count].word[j] = tolower((unsigned char)words[word_count].word[j]);
        }
        words[word_count].word[len] = '\0';
        words[word_count].count = 1;
        
        // Check if word already exists
        int found = 0;
        for (int k = 0; k < word_count; k++) {
            if (strcmp(words[k].word, words[word_count].word) == 0) {
                words[k].count++;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            if (word_count < MAX_WORDS - 1) {
                word_count++;
            }
        }
    }
    
    // Sort words lexicographically using bubble sort
    for (int j = 0; j < word_count - 1; j++) {
        for (int k = 0; k < word_count - 1 - j; k++) {
            if (strcmp(words[k].word, words[k+1].word) > 0) {
                WordEntry temp = words[k];
                words[k] = words[k+1];
                words[k+1] = temp;
            }
        }
    }
    
    // Output
    for (int k = 0; k < word_count; k++) {
        printf("%s %d\n", words[k].word, words[k].count);
    }
    
    return 0;
}
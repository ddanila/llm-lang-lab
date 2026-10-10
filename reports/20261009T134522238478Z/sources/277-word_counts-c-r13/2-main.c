#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 10001

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int main(void) {
    unsigned char buf[10001];
    size_t n = 0;
    
    int c;
    while ((c = getchar()) != EOF && n < 10000) {
        if (isascii(c) && isalpha(c)) {
            buf[n++] = tolower((unsigned char)c);
        } else {
            buf[n++] = '\0';
        }
    }
    
    // Check if we have any word characters at all
    int has_letters = 0;
    for (size_t i = 0; i < n; i++) {
        if (isascii(buf[i]) && isalpha(buf[i])) {
            has_letters = 1;
            break;
        }
    }
    
    if (!has_letters) {
        return 0;
    }
    
    // Parse words from buf
    size_t pos = 0;
    while (pos < n) {
        if (!isascii(buf[pos]) || !isalpha(buf[pos])) {
            pos++;
            continue;
        }
        
        size_t start = pos;
        while (pos < n && isascii(buf[pos]) && isalpha(buf[pos])) {
            pos++;
        }
        
        // Extract word
        size_t len = pos - start;
        char *word = malloc(len + 1);
        if (!word) return 0;
        
        for (size_t i = 0; i < len; i++) {
            word[i] = buf[start + i];
        }
        word[len] = '\0';
        
        // Store in a simple array of structs
        static WordEntry entries[MAX_WORDS];
        static int count = 0;
        
        if (count < MAX_WORDS) {
            strncpy(entries[count].word, word, len);
            entries[count].word[len] = '\0';
            entries[count].count = 0;
            
            // Check if this word already exists in our list
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(entries[i].word, word) == 0) {
                    entries[i].count++;
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                strncpy(entries[count].word, word, len);
                entries[count].word[len] = '\0';
                entries[count].count = 1;
                count++;
            }
            free(word);
        } else {
            free(word);
        }
    }
    
    // Sort words using simple bubble sort (count is at most number of distinct words)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(entries[j].word, entries[j + 1].word) > 0) {
                WordEntry tmp = entries[j];
                
                strcpy(entries[j].word, entries[j + 1].word);
                entries[j].count = entries[j + 1].count;
                
                strcpy(entries[j + 1].word, tmp.word);
                entries[j + 1].count = tmp.count;
            }
        }
    }
    
    // Output results
    for (int i = 0; i < count; i++) {
        printf("%s %d\n", entries[i].word, entries[i].count);
    }
    
    return 0;
}
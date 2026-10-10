#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char word[10005];
    int count;
} entry;

int main(void) {
    unsigned char buf[10005];
    size_t n = 0;
    
    int c;
    while ((c = getchar()) != EOF && n < 10000) {
        buf[n++] = (unsigned char)c;
    }
    
    if (n == 0) {
        return 0;
    }
    
    entry *words = NULL;
    size_t nwords = 0;
    
    for (size_t i = 0; i < n - 1; i++) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            int j = 0;
            while (i < n - 1 && isalpha(buf[i])) {
                words[nwords].word[j++] = tolower((unsigned char)buf[i]);
                i++;
            }
            
            // Check for duplicate
            int found = 0;
            for (size_t k = 0; k < nwords; k++) {
                if (strcmp(words[k].word, words[nwords].word) == 0) {
                    words[k].count++;
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                words = realloc(words, (nwords + 1) * sizeof(entry));
                if (!words) return 1;
                nwords++;
            }
        }
    }
    
    // Handle last word if file ends with letters
    if (n > 0 && isalpha(buf[n - 1])) {
        int j = 0;
        while (n > 0 && isalpha(buf[n - 1])) {
            words[nwords].word[j++] = tolower((unsigned char)buf[n - 1]);
            n--;
        }
        
        // Check for duplicate
        int found = 0;
        for (size_t k = 0; k < nwords; k++) {
            if (strcmp(words[k].word, words[nwords].word) == 0) {
                words[k].count++;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            words = realloc(words, (nwords + 1) * sizeof(entry));
            if (!words) return 1;
            nwords++;
        }
    }
    
    // Sort by ASCII order of word
    for (size_t i = 0; i < nwords - 1; i++) {
        for (size_t j = 0; j < nwords - i - 1; j++) {
            if (strcmp(words[j].word, words[j + 1].word) > 0) {
                entry tmp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tmp;
            }
        }
    }
    
    for (size_t i = 0; i < nwords; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    free(words);
    return 0;
}
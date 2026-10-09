#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LEN 10000

typedef struct {
    char *word;
    int count;
} WordEntry;

int main(void) {
    char buf[MAX_WORD_LEN + 1];
    size_t buf_len = 0;
    
    int n = 0;
    WordEntry words[MAX_WORDS];
    
    int c;
    while ((c = getchar()) != EOF && buf_len < MAX_WORD_LEN) {
        if (isalpha(c)) {
            buf[buf_len++] = (char)tolower(c);
        } else {
            if (buf_len > 0) {
                words[n].word = malloc(buf_len + 1);
                memcpy(words[n].word, buf, buf_len);
                words[n].word[buf_len] = '\0';
                words[n].count = 1;
                
                // Binary search to find position
                int left = 0, right = n;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    int cmp = strcmp(words[n].word, words[mid].word);
                    if (cmp == 0) {
                        words[mid].count++;
                        goto found;
                    } else if (cmp < 0) {
                        right = mid;
                    } else {
                        left = mid + 1;
                    }
                }
                
                // Insert at position 'left'
                memmove(words + left + 1, words + left, (n - left) * sizeof(WordEntry));
                words[left].word = strdup(buf);
                words[left].count = 1;
                n++;
                
            found:;
            buf_len = 0;
        }
    }
    
    // Handle last word if buffer still has content
    if (buf_len > 0) {
        words[n].word = malloc(buf_len + 1);
        memcpy(words[n].word, buf, buf_len);
        words[n].word[buf_len] = '\0';
        
        int left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            int cmp = strcmp(words[n].word, words[mid].word);
            if (cmp == 0) {
                words[mid].count++;
                goto found_last;
            } else if (cmp < 0) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        memmove(words + left + 1, words + left, (n - left) * sizeof(WordEntry));
        words[left].word = strdup(buf);
        words[left].count = 1;
        n++;
        
    found_last:;
    }
    
    // Sort by word
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(words[j].word, words[j + 1].word) > 0) {
                WordEntry temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
    
    // Output
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
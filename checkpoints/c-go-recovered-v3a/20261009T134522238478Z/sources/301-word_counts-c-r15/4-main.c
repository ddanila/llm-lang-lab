#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry*)a)->word, ((WordEntry*)b)->word);
}

int main(void) {
    unsigned char buf[10005];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    
    WordEntry words[MAX_WORDS];
    int word_count = 0;
    
    unsigned char *p = buf;
    unsigned char *end = p + len;
    
    while (p < end) {
        if (*p >= 'A' && *p <= 'Z') {
            *p = *p + 32;
        }
        
        int in_word = (*p >= 'a' && *p <= 'z');
        unsigned char *start = p;
        
        while (p < end && *p >= 'a' && *p <= 'z') {
            p++;
        }
        
        if (in_word) {
            size_t word_len = p - start;
            if (word_count > 0) {
                // Find existing entry
                for (int i = 0; i < word_count; i++) {
                    char *existing = words[i].word;
                    char *found = memchr(buf, *start, word_len);
                    if (strcmp(existing, found) == 0) {
                        words[i].count++;
                        break;
                    }
                }
            } else {
                // First time seeing this word
                if (word_count >= MAX_WORDS) break;
                strncpy(words[word_count].word, (const char*)start, word_len);
                words[word_count].word[word_len] = '\0';
                words[word_count].count = 1;
                word_count++;
            }
        }
    }
    
    // Sort by word lexicographically
    qsort(words, word_count, sizeof(WordEntry), compare_words);
    
    for (int i = 0; i < word_count; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
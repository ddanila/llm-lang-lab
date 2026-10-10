#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 50000
#define MAX_WORD_LEN 10000

static int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int count;
} WordEntry;

int main(void) {
    unsigned char buf[10001];
    size_t len = fread(buf, 1, sizeof(buf), stdin);
    
    if (len == 0) return 0;
    
    // Find first letter start
    int start = -1;
    for (size_t i = 0; i < len; i++) {
        if (isalpha((unsigned char)buf[i])) {
            start = i;
            break;
        }
    }
    if (start == -1) return 0; // No letters
    
    size_t word_start = start;
    size_t word_len = 0;
    
    // Collect words
    WordEntry words[MAX_WORDS];
    int word_count = 0;
    
    for (size_t i = start; i < len; i++) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            if (word_len == 0) {
                // Starting a new word
                words[word_count].count = 0;
                // Copy to lowercase
                for (size_t j = 0; j < i - word_start + 1; j++) {
                    words[word_count].word[j] = tolower(c);
                }
                words[word_count].word[i - word_start + 1] = '\0';
            } else {
                // Continue current word
                words[word_count].word[word_len++] = tolower(c);
            }
        } else {
            if (word_len > 0) {
                words[word_count].word[word_len] = '\0';
                word_count++;
                word_start = i + 1;
                word_len = 0;
            }
        }
    }
    
    // Handle last word if exists
    if (word_len > 0) {
        words[word_count].word[word_len] = '\0';
        word_count++;
    }
    
    if (word_count == 0) return 0;
    
    // Convert to array of pointers for qsort
    char *ptrs[MAX_WORDS];
    for (int i = 0; i < word_count; i++) {
        ptrs[i] = words[i].word;
    }
    
    qsort(ptrs, word_count, sizeof(char *), cmp);
    
    // Now count consecutive duplicates and output
    char current[MAX_WORD_LEN + 1];
    strcpy(current, ptrs[0]);
    int ccount = 0;
    
    for (int i = 0; i < word_count; i++) {
        if (strcmp(ptrs[i], current) == 0) {
            ccount++;
        } else {
            printf("%s %d\n", current, ccount);
            strcpy(current, ptrs[i]);
            ccount = 1;
        }
    }
    printf("%s %d\n", current, ccount);
    
    return 0;
}
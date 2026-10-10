#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_BYTES 10000
#define MAX_WORDS 65536
#define MAX_WORD_LEN 10000

typedef struct {
    char word[MAX_WORD_LEN + 1];
    int count;
} WordEntry;

static WordEntry words[MAX_WORDS];
static int num_words = 0;

static void add_word(const char *word) {
    if (num_words >= MAX_WORDS) return;
    
    // Check if word already exists
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i].word, word) == 0) {
            words[i].count++;
            return;
        }
    }
    
    // Add new word
    strncpy(words[num_words].word, word, MAX_WORD_LEN);
    words[num_words].word[MAX_WORD_LEN] = '\0';
    words[num_words].count = 1;
    num_words++;
}

int main(void) {
    char buf[MAX_BYTES];
    size_t pos = 0;
    int c;
    
    // Read all input into buffer
    while ((c = getchar()) != EOF && pos < MAX_BYTES - 1) {
        buf[pos++] = (char)c;
    }
    buf[pos] = '\0';
    
    printf("DEBUG: Buffer length = %zu\n", pos);
    printf("DEBUG: Buffer content = %s\n", buf);
    
    // Parse words from buffer
    size_t i = 0;
    while (i < pos) {
        if (isalpha((unsigned char)buf[i])) {
            // Start of a word, collect until non-alpha or end
            size_t j = i;
            while (j < pos && isalpha((unsigned char)buf[j])) {
                j++;
            }
            
            // Extract and lowercase the word
            size_t len = j - i;
            if (len > 0 && len <= MAX_WORD_LEN) {
                for (size_t k = i; k < j; k++) {
                    buf[k] = tolower((unsigned char)buf[k]);
                }
                add_word(&buf[i]);
            }
            
            // Move past this word
            i = j;
        } else {
            // Non-letter character, skip it
            i++;
        }
    }
    
    printf("DEBUG: num_words = %d\n", num_words);
    
    // Sort words lexicographically using bubble sort for simplicity
    if (num_words > 0) {
        for (int start = 0; start < num_words - 1; start++) {
            int min_idx = start;
            for (int j = start + 1; j < num_words; j++) {
                if (strcmp(words[j].word, words[min_idx].word) < 0) {
                    min_idx = j;
                }
            }
            if (min_idx != start) {
                WordEntry temp = words[start];
                words[start] = words[min_idx];
                words[min_idx] = temp;
            }
        }
    }
    
    // Output
    for (int i = 0; i < num_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
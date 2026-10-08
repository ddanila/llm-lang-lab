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

static int compare_words(const void *a, const void *b) {
    return strcmp(((WordEntry*)a)->word, ((WordEntry*)b)->word);
}

int main(void) {
    char buf[MAX_BYTES];
    size_t total = 0;
    int c;
    
    // Read input byte by byte until EOF or limit
    while ((c = getchar()) != EOF && total < MAX_BYTES - 1) {
        if (isalpha(c)) {
            if (total == 0) {
                // First letter of first word
                char word[MAX_WORD_LEN + 1];
                int len = 0;
                
                while (c != EOF && isalpha(c) && len < MAX_WORD_LEN) {
                    word[len++] = tolower((unsigned char)c);
                    c = getchar();
                }
                word[len] = '\0';
                add_word(word);
            } else {
                // Continuing a word
                char *p = &buf[total];
                while (c != EOF && isalpha(c) && total < MAX_BYTES - 1) {
                    p[total++] = tolower((unsigned char)c);
                    c = getchar();
                }
                if (c == EOF || !isalpha(c)) {
                    buf[total] = '\0';
                    add_word(buf);
                }
            }
        } else {
            // Non-letter byte - if we were collecting a word, it ends here
            if (total > 0) {
                buf[total] = '\0';
                add_word(buf);
                total = 0;
            }
            if (c != EOF) {
                c = getchar(); // Consume the non-letter char
            }
        }
    }
    
    // Handle any remaining word at EOF
    if (total > 0) {
        buf[total] = '\0';
        add_word(buf);
    }
    
    // Sort words lexicographically
    qsort(words, num_words, sizeof(WordEntry), compare_words);
    
    // Output
    for (int i = 0; i < num_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}
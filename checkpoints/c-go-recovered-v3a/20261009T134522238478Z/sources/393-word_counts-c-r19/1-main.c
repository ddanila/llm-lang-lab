#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int main(void) {
    unsigned char buf[10000];
    size_t len = fread(buf, 1, sizeof(buf), stdin);

    WordEntry words[MAX_WORDS];
    int n_words = 0;
    
    // We'll use a simple approach: collect current word chars into a buffer,
    // then when we hit a separator or EOF, process the word.
    char current_word[MAX_WORD_LEN + 1] = {0};
    size_t cur_len = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            // Append to current word
            if (cur_len < MAX_WORD_LEN) {
                current_word[cur_len++] = (char)c;
            }
        } else {
            // Separator - process current word if any
            if (cur_len > 0) {
                // Convert to lowercase
                for (size_t j = 0; j < cur_len; j++) {
                    current_word[j] = tolower((unsigned char)current_word[j]);
                }
                
                // Check if word already exists
                int found = 0;
                for (int w = 0; w < n_words; w++) {
                    size_t wlen = strlen(words[w].word);
                    if (wlen == cur_len) {
                        int match = 1;
                        for (size_t j = 0; j < wlen; j++) {
                            if (words[w].word[j] != current_word[j]) {
                                match = 0;
                                break;
                            }
                        }
                        if (match) {
                            words[w].count++;
                            found = 1;
                            break;
                        }
                    }
                }
                
                if (!found) {
                    // Add new word
                    if (n_words < MAX_WORDS) {
                        strncpy(words[n_words].word, current_word, cur_len);
                        words[n_words].count = 1;
                        n_words++;
                    }
                }
            }
            current_word[0] = '\0';
            cur_len = 0;
        }
    }

    // Process any remaining word at EOF
    if (cur_len > 0) {
        for (size_t j = 0; j < cur_len; j++) {
            current_word[j] = tolower((unsigned char)current_word[j]);
        }
        
        int found = 0;
        for (int w = 0; w < n_words; w++) {
            size_t wlen = strlen(words[w].word);
            if (wlen == cur_len) {
                int match = 1;
                for (size_t j = 0; j < wlen; j++) {
                    if (words[w].word[j] != current_word[j]) {
                        match = 0;
                        break;
                    }
                }
                if (match) {
                    words[w].count++;
                    found = 1;
                    break;
                }
            }
        }
        
        if (!found) {
            if (n_words < MAX_WORDS) {
                strncpy(words[n_words].word, current_word, cur_len);
                words[n_words].count = 1;
                n_words++;
            }
        }
    }

    // Sort words lexicographically by word string
    for (int i = 0; i < n_words - 1; i++) {
        for (int j = 0; j < n_words - i - 1; j++) {
            if (strcmp(words[j].word, words[j+1].word) > 0) {
                WordEntry temp = words[j];
                words[j] = words[j+1];
                words[j+1] = temp;
            }
        }
    }

    // Output results
    for (int i = 0; i < n_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    return 0;
}
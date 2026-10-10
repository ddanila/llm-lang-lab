#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

int compare_words(const void *a, const void *b) {
    const WordEntry *wa = (const WordEntry *)a;
    const WordEntry *wb = (const WordEntry *)b;
    return strcmp(wa->word, wb->word);
}

int main(void) {
    unsigned char buf[10000];
    size_t len = fread(buf, 1, sizeof(buf), stdin);

    // Use a dynamic approach with linked list for words to avoid O(n^2) search
    WordEntry *words = malloc(MAX_WORDS * sizeof(WordEntry));
    if (!words) {
        return 0;
    }
    
    int n_words = 0;
    
    char current_word[MAX_WORD_LEN + 1] = {0};
    size_t cur_len = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            if (cur_len < MAX_WORD_LEN) {
                current_word[cur_len++] = (char)c;
            }
        } else {
            if (cur_len > 0) {
                for (size_t j = 0; j < cur_len; j++) {
                    current_word[j] = tolower((unsigned char)current_word[j]);
                }
                
                // Check if word already exists using binary search or linear scan
                int found = 0;
                int insert_pos = -1;
                
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
                    // Insert in sorted order
                    int i = n_words - 1;
                    while (i >= 0 && strcmp(words[i].word, current_word) > 0) {
                        words[i + 1] = words[i];
                        i--;
                    }
                    
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
            int i = n_words - 1;
            while (i >= 0 && strcmp(words[i].word, current_word) > 0) {
                words[i + 1] = words[i];
                i--;
            }
            
            if (n_words < MAX_WORDS) {
                strncpy(words[n_words].word, current_word, cur_len);
                words[n_words].count = 1;
                n_words++;
            }
        }
    }

    // Sort all words
    qsort(words, n_words, sizeof(WordEntry), compare_words);

    // Output results
    for (int i = 0; i < n_words; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    free(words);
    return 0;
}
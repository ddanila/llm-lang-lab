#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 65536
#define MAX_WORD_LEN 10000

int word_count[MAX_WORDS];
char word_str[MAX_WORDS][MAX_WORD_LEN + 1];
int word_cnt = 0;

int main(void) {
    unsigned char buf[10000 + 1];
    size_t n = 0;
    
    int c;
    while ((c = getchar()) != EOF && n < sizeof(buf)) {
        buf[n++] = (unsigned char)c;
    }
    buf[n] = '\0';

    int len = strlen((char *)buf);
    int i = 0;
    
    // First pass: collect all words and count them
    while (i < len) {
        if (isalpha(buf[i])) {
            // Start of a word
            int start = i;
            while (i < len && isalpha(buf[i])) {
                i++;
            }
            int wlen = i - start;
            if (wlen > 0) {
                char w[MAX_WORD_LEN + 1];
                for (int j = 0; j < wlen; j++) {
                    w[j] = tolower(buf[start + j]);
                }
                w[wlen] = '\0';
                
                // Find existing word or add new one
                int found = -1;
                for (int k = 0; k < word_cnt; k++) {
                    if (strcmp(word_str[k], w) == 0) {
                        found = k;
                        break;
                    }
                }
                
                if (found >= 0) {
                    word_count[found]++;
                } else {
                    // Insert at position word_cnt
                    if (word_cnt >= MAX_WORDS) {
                        fprintf(stderr, "Too many words\n");
                        return 1;
                    }
                    memmove(word_str + word_cnt + 1, word_str + word_cnt, 
                            (MAX_WORDS - word_cnt - 1) * sizeof(char[MAX_WORD_LEN + 1]));
                    memmove(word_count + word_cnt + 1, word_count + word_cnt, 
                            (MAX_WORDS - word_cnt - 1) * sizeof(int));
                    
                    if (wlen > MAX_WORD_LEN) wlen = MAX_WORD_LEN;
                    for (int j = 0; j < wlen; j++) {
                        word_str[word_cnt][j] = w[j];
                    }
                    word_str[word_cnt][wlen] = '\0';
                    word_count[word_cnt] = 1;
                    word_cnt++;
                }
            }
        } else {
            i++;
        }
    }

    // Sort words lexicographically
    for (int a = 0; a < word_cnt - 1; a++) {
        for (int b = 0; b < word_cnt - a - 1; b++) {
            if (strcmp(word_str[b], word_str[b + 1]) > 0) {
                char tmp[10002];
                strcpy(tmp, word_str[b]);
                strcpy(word_str[b], word_str[b + 1]);
                strcpy(word_str[b + 1], tmp);
                
                int t = word_count[b];
                word_count[b] = word_count[b + 1];
                word_count[b + 1] = t;
            }
        }
    }

    for (int i = 0; i < word_cnt; i++) {
        printf("%s %d\n", word_str[i], word_count[i]);
    }

    return 0;
}
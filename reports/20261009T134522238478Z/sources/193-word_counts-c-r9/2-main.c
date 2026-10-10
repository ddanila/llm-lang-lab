#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    unsigned char buf[10000];
    size_t len = fread(buf, 1, sizeof(buf), stdin);

    struct Word {
        char text[10001];
        int len;
        int count;
    };

    static struct Word words[256];
    int word_count = 0;

    char current_word[10001];
    size_t cur_len = 0;

    for (size_t i = 0; i < len; ++i) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            current_word[cur_len++] = (char)tolower(c);
        } else {
            if (cur_len > 0) {
                current_word[cur_len] = '\0';
                int found = -1;
                for (int j = 0; j < word_count; ++j) {
                    if (strcmp(words[j].text, current_word) == 0) {
                        words[j].count++;
                        found = j;
                        break;
                    }
                }
                if (found == -1) {
                    strcpy(words[word_count].text, current_word);
                    words[word_count].len = cur_len;
                    words[word_count].count = 1;
                    word_count++;
                }
                cur_len = 0;
            }
        }
    }

    if (cur_len > 0) {
        current_word[cur_len] = '\0';
        int found = -1;
        for (int j = 0; j < word_count; ++j) {
            if (strcmp(words[j].text, current_word) == 0) {
                words[j].count++;
                found = j;
                break;
            }
        }
        if (found == -1) {
            strcpy(words[word_count].text, current_word);
            words[word_count].len = cur_len;
            words[word_count].count = 1;
            word_count++;
        }
    }

    for (int i = 0; i < word_count - 1; ++i) {
        for (int j = 0; j < word_count - i - 1; ++j) {
            if (strcmp(words[j].text, words[j + 1].text) > 0) {
                struct Word tmp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < word_count; ++i) {
        printf("%s %d\n", words[i].text, words[i].count);
    }

    return 0;
}
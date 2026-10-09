#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 5000
#define MAX_WORD_LEN 10001

int main(void) {
    char buf[10001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    typedef struct { char w[MAX_WORD_LEN]; size_t len; int count; } Entry;
    static Entry entries[MAX_WORDS];
    int wcount = 0;
    
    int in_word = 0;
    char current_word[MAX_WORD_LEN];
    size_t cur_len = 0;
    
    for (size_t i = 0; i < n; i++) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            if (!in_word) {
                in_word = 1;
                cur_len = 0;
                current_word[cur_len++] = (char)c;
            } else {
                current_word[cur_len++] = (char)c;
            }
        } else {
            if (in_word) {
                entries[wcount].len = cur_len;
                memcpy(entries[wcount].w, current_word, cur_len);
                wcount++;
                in_word = 0;
                cur_len = 0;
            }
        }
    }
    
    if (in_word) {
        entries[wcount].len = cur_len;
        memcpy(entries[wcount].w, current_word, cur_len);
        wcount++;
    }
    
    for (int i = 0; i < wcount; i++) {
        for (size_t j = 0; j < entries[i].len; j++) {
            entries[i].w[j] = tolower((unsigned char)entries[i].w[j]);
        }
    }
    
    for (int i = 1; i < wcount; i++) {
        Entry key = entries[i];
        int j = i - 1;
        while (j >= 0 && strcmp(entries[j].w, key.w) > 0) {
            entries[j + 1] = entries[j];
            j--;
        }
        entries[j + 1] = key;
    }
    
    int out_count = 0;
    if (wcount > 0) {
        for (int i = 0; i < wcount; i++) {
            if (i == 0 || strcmp(entries[i].w, entries[i-1].w) != 0) {
                out_count++;
                Entry *dest = &entries[out_count - 1];
                memcpy(dest->w, entries[i].w, entries[i].len);
                dest->len = entries[i].len;
                dest->count = 1;
            } else {
                entries[out_count - 1].count++;
            }
        }
    }
    
    for (int i = 0; i < out_count; i++) {
        printf("%s %d\n", entries[i].w, entries[i].count);
    }
    
    return 0;
}
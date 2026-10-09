#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_LEN 10005

typedef struct {
    char word[MAX_LEN];
    int count;
} WordEntry;

int find_word(WordEntry words[], int n, const char *word) {
    for (int i = 0; i < n; i++) {
        if (strcmp(words[i].word, word) == 0) return i;
    }
    return -1;
}

int main(void) {
    char buffer[10005];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    buffer[len] = '\0';

    WordEntry words[MAX_WORDS];
    int n = 0;

    for (size_t i = 0; i < len; ) {
        if (!isalpha((unsigned char)buffer[i])) {
            i++;
            continue;
        }
        size_t j = i + 1;
        while (j < len && isalpha((unsigned char)buffer[j])) {
            j++;
        }
        int wlen = j - i;
        if (wlen == 0) continue;

        // Convert to lowercase
        for (int k = 0; k < wlen; k++) {
            words[n].word[k] = tolower((unsigned char)buffer[i + k]);
        }
        words[n].word[wlen] = '\0';

        int idx = find_word(words, n, words[n].word);
        if (idx != -1) {
            words[idx].count++;
        } else {
            strcpy(words[n].word, words[n].word); // redundant but clear
            words[n].count = 1;
            n++;
        }

        i = j;
    }

    // Sort by word (lexicographic)
    for (int a = 0; a < n - 1; a++) {
        for (int b = 0; b < n - a - 1; b++) {
            if (strcmp(words[b].word, words[b + 1].word) > 0) {
                WordEntry tmp = words[b];
                words[b] = words[b + 1];
                words[b + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

    return 0;
}
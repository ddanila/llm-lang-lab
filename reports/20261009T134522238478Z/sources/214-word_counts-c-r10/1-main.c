#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_LEN 200

typedef struct {
    char word[MAX_LEN];
    int count;
} WordCount;

int compare_words(const void *a, const void *b) {
    return strcmp(((WordCount *)a)->word, ((WordCount *)b)->word);
}

int main(void) {
    unsigned char buf[10000];
    size_t len = 0;
    int c;

    while ((c = getchar()) != EOF && len < 10000) {
        if (isascii(c) && isalpha(c)) {
            buf[len++] = (unsigned char)tolower(c);
        } else if (len > 0) {
            // Word ended
            for (int i = 0; i < len; i++) {
                putchar(buf[i]);
            }
            putchar('\n');
            len = 0;
        }
    }

    if (len > 0) {
        // Flush remaining word
        for (size_t i = 0; i < len; i++) {
            putchar(buf[i]);
        }
        putchar('\n');
    }

    return 0;
}
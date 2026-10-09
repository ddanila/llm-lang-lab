#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BYTES 10000

typedef struct {
    const char *ptr;
    size_t len;
} Entry;

static int compare_entries(const void *a, const void *b) {
    const Entry *ea = (const Entry *)a;
    const Entry *eb = (const Entry *)b;
    size_t la = ea->len;
    size_t lb = eb->len;
    size_t i = 0;
    while (i < la && i < lb) {
        unsigned char ca = tolower((unsigned char)ea->ptr[i]);
        unsigned char cb = tolower((unsigned char)eb->ptr[i]);
        if (ca != cb) return ca - cb;
        i++;
    }
    if (la != lb) return la - lb;
    return 0;
}

int main(void) {
    unsigned char buf[MAX_BYTES];
    size_t n = fread(buf, 1, MAX_BYTES, stdin);

    static Entry entries[MAX_BYTES];
    int ec = 0;

    size_t i = 0;
    while (i < n) {
        if (isalpha((unsigned char)buf[i])) {
            size_t len = 0;
            while (i + len < n && isalpha((unsigned char)buf[i + len])) {
                len++;
            }
            entries[ec].ptr = (const char *)buf + i;
            entries[ec].len = len;
            ec++;
            i += len;
        } else {
            i++;
        }
    }

    if (ec == 0) return 0;

    qsort(entries, ec, sizeof(Entry), compare_entries);

    for (int k = 0; k < ec; ) {
        size_t len = entries[k].len;
        char *word_str = malloc(len + 1);
        for (size_t j = 0; j < len; j++) {
            word_str[j] = tolower((unsigned char)entries[k].ptr[j]);
        }
        word_str[len] = '\0';

        int count = 1;
        k++;
        while (k < ec && entries[k].len == len) {
            int match = 1;
            for (size_t j = 0; j < len; j++) {
                unsigned char c1 = tolower((unsigned char)entries[k-1].ptr[j]);
                unsigned char c2 = tolower((unsigned char)entries[k].ptr[j]);
                if (c1 != c2) {
                    match = 0;
                    break;
                }
            }
            if (!match) break;
            count++;
            k++;
        }
        printf("%s %d\n", word_str, count);
        free(word_str);
    }

    return 0;
}
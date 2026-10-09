#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BYTES 10000

int main(void) {
    unsigned char buf[MAX_BYTES];
    size_t n = fread(buf, 1, MAX_BYTES, stdin);

    // Collect all words (lowercased) into an array of strings.
    // We'll use a simple dynamic array of word pointers and lengths.
    typedef struct {
        const char *str;
        size_t len;
    } Word;

    static Word words[MAX_BYTES]; // worst case: one letter per byte
    int wcount = 0;

    size_t i = 0;
    while (i < n) {
        unsigned char c = buf[i];
        if (isalpha(c)) {
            size_t len = 0;
            while (i + len < n && isalpha(buf[i + len])) {
                // store lowercase
                words[wcount].str = &buf[i + len] - (c == buf[i]); // careful, better approach below
                len++;
            }
        } else {
            i++;
            continue;
        }
    }

    // Re-implement cleanly:
    // We'll do a single pass to collect words into a fixed-size array.
    // Since each word is at least 1 char and max 10000, but total bytes <= 10000,
    // we can't have more than MAX_BYTES words.

    static Word wlist[MAX_BYTES];
    int wc = 0;

    i = 0;
    while (i < n) {
        if (isalpha(buf[i])) {
            size_t len = 0;
            while (i + len < n && isalpha(buf[i + len])) {
                len++;
            }
            // Store the word starting at i, lowercased.
            for (size_t j = 0; j < len; j++) {
                wlist[wc].str = buf + i + j;
                wlist[wc].len = 1;
            }
            wc++;
            i += len;
        } else {
            i++;
        }
    }

    // Now we have wc words. We need to count frequencies and output sorted by lowercase word.
    // Since MAX_BYTES is small (10000), we can use a simple counting sort over ASCII range? 
    // But words are up to 10000 letters, so we cannot use array of size 26*10000 easily.
    // Instead, we'll collect distinct words and their counts using a dynamic approach or qsort+unique.

    // Approach: Use an array of structs with word string (pointer) and count, then sort and unique.
    // But we need to lowercase the stored words for comparison and output.

    // Let's re-collect words into an array of struct { char *data; size_t len; } and lower-case them.
    // Since total bytes <= 10000, we can allocate a contiguous buffer for all words? Not straightforward.
    // Simpler: Use a dynamic array of word structs, each storing the word as a string in a global pool.

    // Given constraints, let's do this:
    // 1. Collect all words into an array of (char *word, size_t len) where word points into buf (but we need to lowercase).
    //    Instead, we can create a new buffer for lowercased words? But that might exceed memory if many words.
    //    However, total bytes <= 10000, so even if we duplicate each byte, it's fine.

    // Let's use a simple approach: 
    // - Create an array of word structs where each word is stored as a string in a separate buffer? 
    //   But we don't want to allocate too much. 
    //   Alternative: Use a single buffer for all words, but that's complex.

    // Given the small total size (10000 bytes), we can do:
    // - Store each word as a string in a char array of size 10000*2? Not safe.
    //   Instead, use an array of pointers to substrings of buf, and lower-case them when comparing.

    // But for sorting and counting, we need to compare lowercased versions.
    // We can create an array of struct { const char *ptr; size_t len; } and then sort by lowercased ptr.

    // Let's do:
    typedef struct {
        const char *ptr;
        size_t len;
    } Entry;

    static Entry entries[MAX_BYTES];
    int ec = 0;

    i = 0;
    while (i < n) {
        if (isalpha(buf[i])) {
            size_t len = 0;
            while (i + len < n && isalpha(buf[i + len])) {
                len++;
            }
            entries[ec].ptr = buf + i;
            entries[ec].len = len;
            ec++;
            i += len;
        } else {
            i++;
        }
    }

    // Now sort entries by lowercased string.
    // We'll use qsort with a custom comparator that lowercases on the fly.

    int compare_entries(const void *a, const void *b) {
        const Entry *ea = (const Entry *)a;
        const Entry *eb = (const Entry *)b;
        size_t la = ea->len;
        size_t lb = eb->len;
        size_t i = 0;
        while (i < la && i < lb) {
            unsigned char ca = tolower(ea->ptr[i]);
            unsigned char cb = tolower(eb->ptr[i]);
            if (ca != cb) return ca - cb;
            i++;
        }
        if (la != lb) return la - lb;
        return 0;
    }

    qsort(entries, ec, sizeof(Entry), compare_entries);

    // Now iterate and count consecutive identical words.
    for (int k = 0; k < ec; ) {
        size_t len = entries[k].len;
        char *word_str = malloc(len + 1);
        for (size_t j = 0; j < len; j++) {
            word_str[j] = tolower(entries[k].ptr[j]);
        }
        word_str[len] = '\0';

        int count = 1;
        k++;
        while (k < ec && entries[k].len == len) {
            // Check if lowercased matches
            int match = 1;
            for (size_t j = 0; j < len; j++) {
                unsigned char c1 = tolower(entries[k-1].ptr[j]);
                unsigned char c2 = tolower(entries[k].ptr[j]);
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
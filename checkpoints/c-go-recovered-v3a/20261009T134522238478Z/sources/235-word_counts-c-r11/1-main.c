#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

int main(void) {
    char buffer[10005];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    // Hash table: word -> count
    // We'll use a simple approach: collect words, sort them, then count consecutive duplicates
    // But we need to output in lexicographic order.
    // Let's read all words into an array, then sort and count.
    
    char *words[MAX_WORDS];
    int word_count = 0;
    char current_word[MAX_WORD_LEN];
    size_t cur_len = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = buffer[i];
        if (isalpha(c)) {
            // lowercase it
            current_word[cur_len++] = tolower((unsigned char)c);
        } else {
            if (cur_len > 0) {
                words[word_count] = current_word;
                word_count++;
                cur_len = 0;
            }
        }
    }
    
    // Handle last word if any
    if (cur_len > 0) {
        words[word_count] = current_word;
        word_count++;
    }
    
    if (word_count == 0) {
        return 0;
    }
    
    // Sort words using bubble sort or qsort. Let's use a simple approach since we can't easily use qsort with char*.
    // Actually, let's implement a simple insertion sort for small arrays, but word_count could be large.
    // Better: use qsort with a custom comparator.
    
    // Since we can't include <stdlib.h> for qsort in the standard library? We can, it's part of stdlib.
    // But let's just implement a simple sort to avoid any issues.
    
    // Insertion sort
    for (int i = 1; i < word_count; i++) {
        char *temp = words[i];
        int j = i - 1;
        while (j >= 0 && strcmp(words[j], temp) > 0) {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = temp;
    }
    
    // Now count consecutive duplicates and output
    char *prev = words[0];
    int count = 1;
    for (int i = 1; i < word_count; i++) {
        if (strcmp(words[i], prev) == 0) {
            count++;
        } else {
            printf("%s %d\n", prev, count);
            prev = words[i];
            count = 1;
        }
    }
    // Output last word
    printf("%s %d\n", prev, count);
    
    return 0;
}
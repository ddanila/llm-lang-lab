#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BYTES 10000
#define HASH_SIZE 10007

typedef struct {
    char word[HASH_SIZE];
    int count;
} WordEntry;

WordEntry hash_table[HASH_SIZE];

static int hash(const char *word) {
    unsigned long h = 5381;
    for (int i = 0; word[i] != '\0'; i++) {
        h = ((h << 5) + h) + (unsigned char)word[i];
    }
    return (int)(h % HASH_SIZE);
}

static int find_or_insert(const char *word, int len) {
    int idx = hash(word);
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash_table[i].count == 0) {
            strncpy(hash_table[i].word, word, len + 1);
            hash_table[i].count = 1;
            return idx;
        } else if (strcmp(hash_table[i].word, word) == 0) {
            hash_table[i].count++;
            return idx;
        } else {
            int next_idx = (idx + i + 1) % HASH_SIZE;
            if (hash_table[next_idx].count == 0) {
                strncpy(hash_table[next_idx].word, word, len + 1);
                hash_table[next_idx].count = 1;
                return next_idx;
            } else if (strcmp(hash_table[next_idx].word, word) == 0) {
                hash_table[next_idx].count++;
                return next_idx;
            }
        }
    }
    return -1;
}

int main(void) {
    char buffer[MAX_BYTES];
    size_t total_len = 0;
    int c;
    
    while ((c = getchar()) != EOF && total_len < MAX_BYTES) {
        buffer[total_len++] = (char)c;
    }
    buffer[total_len] = '\0';
    
    // Find all words and store in a list for sorting
    int idx = -1;
    int start = -1;
    
    for (size_t i = 0; i < total_len; i++) {
        if (isalpha((unsigned char)buffer[i])) {
            if (start == -1) {
                start = i;
            }
        } else {
            if (start != -1) {
                size_t len = i - start;
                idx = find_or_insert(&buffer[start], len);
                start = -1;
            }
        }
    }
    
    // Handle word at end of buffer
    if (start != -1) {
        size_t len = total_len - start;
        idx = find_or_insert(&buffer[start], len);
    }
    
    // Create an array of indices and sort them based on word content
    int *indices = malloc(HASH_SIZE * sizeof(int));
    if (!indices) return 0;
    
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash_table[i].count > 0) {
            indices[0] = i;
        }
    }
    
    int count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash_table[i].count > 0) {
            indices[count++] = i;
        }
    }
    
    // Bubble sort the indices based on word content
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int a_idx = indices[j];
            int b_idx = indices[j + 1];
            if (strcmp(hash_table[a_idx].word, hash_table[b_idx].word) > 0) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
    
    // Output sorted results
    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        printf("%s %d\n", hash_table[idx].word, hash_table[idx].count);
    }
    
    free(indices);
    return 0;
}
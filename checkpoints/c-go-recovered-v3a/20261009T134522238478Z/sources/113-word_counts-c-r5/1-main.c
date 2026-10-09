#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char buffer[10000];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    if (len == 0) {
        return 0;
    }
    
    // Convert entire buffer to lowercase and process
    for (size_t i = 0; i < len; i++) {
        buffer[i] = tolower((unsigned char)buffer[i]);
    }
    
    // Collect words
    // We'll use a simple array of strings, but need to handle duplicates
    // Since we need lexicographic order and counts, let's use a linked list approach
    // or just collect all words and then sort/count.
    
    // Actually, let's use a simpler approach: 
    // Collect all words into an array, then sort and count consecutive duplicates.
    
    int word_count = 0;
    char *words[10000]; // Max possible words is len
    
    const char *ptr = buffer;
    while (ptr < buffer + len) {
        const char *start = ptr;
        // Skip non-letter characters
        while (ptr < buffer + len && !isalpha((unsigned char)*ptr)) {
            ptr++;
        }
        if (ptr >= buffer + len) break;
        
        const char *end = ptr;
        // Read word
        while (ptr < buffer + len && isalpha((unsigned char)*ptr)) {
            ptr++;
        }
        
        size_t wlen = end - start;
        if (wlen > 0) {
            words[word_count] = malloc(wlen + 1);
            memcpy(words[word_count], start, wlen);
            words[word_count][wlen] = '\0';
            word_count++;
        }
    }
    
    // Sort the words array (bubble sort or similar)
    for (int i = 0; i < word_count - 1; i++) {
        for (int j = 0; j < word_count - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                char *temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
    
    // Output counts for consecutive duplicates
    if (word_count > 0) {
        int current_count = 1;
        printf("%s %d\n", words[0], current_count);
        
        for (int i = 1; i < word_count; i++) {
            if (strcmp(words[i], words[i - 1]) == 0) {
                current_count++;
            } else {
                printf("%s %d\n", words[i], current_count);
                current_count = 1;
            }
        }
    }
    
    // Free allocated memory
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    
    return 0;
}
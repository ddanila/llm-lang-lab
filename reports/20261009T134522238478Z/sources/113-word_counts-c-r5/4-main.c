#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char buffer[10000];
    size_t len = fread(buffer, 1, sizeof(buffer), stdin);
    
    // Collect words directly into a simple array without pre-converting to lowercase
    int word_count = 0;
    char *words[10000]; 
    
    const char *ptr = buffer;
    while (ptr < buffer + len) {
        // Skip non-letter characters
        while (ptr < buffer + len && !isalpha((unsigned char)*ptr)) {
            ptr++;
        }
        if (ptr >= buffer + len) break;
        
        const char *start = ptr;
        const char *end = ptr;
        // Read word
        while (ptr < buffer + len && isalpha((unsigned char)*ptr)) {
            ptr++;
        }
        
        size_t wlen = end - start;
        if (wlen > 0) {
            words[word_count] = malloc(wlen + 1);
            memcpy(words[word_count], start, wlen);
            // Convert to lowercase
            for (size_t i = 0; i < wlen; i++) {
                words[word_count][i] = tolower((unsigned char)words[word_count][i]);
            }
            word_count++;
        }
    }
    
    // Sort the words array
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
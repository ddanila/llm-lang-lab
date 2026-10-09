#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void) {
    unsigned char buf[10001];
    size_t n = 0;
    
    int c;
    while ((c = getchar()) != EOF && n < 10000) {
        if (isascii(c) && isalpha(c)) {
            buf[n++] = tolower((unsigned char)c);
        } else {
            buf[n++] = '\0';
        }
    }
    
    // Check if we have any word characters at all
    int has_letters = 0;
    for (size_t i = 0; i < n; i++) {
        if (isascii(buf[i]) && isalpha(buf[i])) {
            has_letters = 1;
            break;
        }
    }
    
    if (!has_letters) {
        return 0;
    }
    
    // Parse words from buf
    size_t pos = 0;
    while (pos < n) {
        if (!isascii(buf[pos]) || !isalpha(buf[pos])) {
            pos++;
            continue;
        }
        
        size_t start = pos;
        while (pos < n && isascii(buf[pos]) && isalpha(buf[pos])) {
            pos++;
        }
        
        // Extract word
        size_t len = pos - start;
        char *word = malloc(len + 1);
        if (!word) return 0;
        
        for (size_t i = 0; i < len; i++) {
            word[i] = buf[start + i];
        }
        word[len] = '\0';
        
        // Store in a simple array of structs
        static char words[10000][10001];
        static int counts[10000];
        static int count = 0;
        
        if (count < 10000) {
            strncpy(words[count], word, len);
            words[count][len] = '\0';
            counts[count] = 0;
            
            // Check if this word already exists in our list
            int found = 0;
            for (int i = 0; i < count; i++) {
                if (strcmp(words[i], word) == 0) {
                    counts[i]++;
                    found = 1;
                    break;
                }
            }
            
            if (!found) {
                strncpy(words[count], word, len);
                words[count][len] = '\0';
                counts[count] = 1;
                count++;
            }
            free(word);
        } else {
            free(word);
        }
    }
    
    // Sort words using simple bubble sort (count is at most number of distinct words)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                char tmp[10001];
                int tmp_count;
                strcpy(tmp, words[j]);
                tmp_count = counts[j];
                
                strcpy(words[j], words[j + 1]);
                counts[j] = counts[j + 1];
                
                strcpy(words[j + 1], tmp);
                counts[j + 1] = tmp_count;
            }
        }
    }
    
    // Output results
    for (int i = 0; i < count; i++) {
        printf("%s %d\n", words[i], counts[i]);
    }
    
    return 0;
}
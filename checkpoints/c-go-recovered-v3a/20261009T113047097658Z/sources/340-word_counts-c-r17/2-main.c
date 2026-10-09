#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10005
#define MAX_WORD_LEN 10005

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} Entry;

int compare(const void *a, const void *b) {
    return strcmp(((Entry*)a)->word, ((Entry*)b)->word);
}

int main(void) {
    char buf[MAX_WORD_LEN];
    size_t len = 0;
    
    Entry entries[MAX_WORDS];
    int num_entries = 0;
    
    int c;
    while ((c = getchar()) != EOF) {
        if (isalpha((unsigned char)c)) {
            buf[len++] = (char)tolower((unsigned char)c);
        } else {
            if (len > 0) {
                // Find existing word
                for (int i = 0; i < num_entries; i++) {
                    if (strcmp(entries[i].word, buf) == 0) {
                        entries[i].count++;
                        break;
                    }
                }
                
                // If not found, add new entry
                int found = 0;
                for (int i = 0; i < num_entries; i++) {
                    if (entries[i].word[0] == '\0') {
                        strcpy(entries[i].word, buf);
                        entries[i].count = 1;
                        found = 1;
                        break;
                    }
                }
                
                // If no empty slot, find existing word and increment
                if (!found) {
                    for (int i = 0; i < num_entries; i++) {
                        if (strcmp(entries[i].word, buf) == 0) {
                            entries[i].count++;
                            break;
                        }
                    }
                }
                
                len = 0;
            }
        }
    }
    
    // Handle last word if any
    if (len > 0) {
        for (int i = 0; i < num_entries; i++) {
            if (strcmp(entries[i].word, buf) == 0) {
                entries[i].count++;
                break;
            }
        }
        
        int found = 0;
        for (int i = 0; i < num_entries; i++) {
            if (entries[i].word[0] == '\0') {
                strcpy(entries[i].word, buf);
                entries[i].count = 1;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            for (int i = 0; i < num_entries; i++) {
                if (strcmp(entries[i].word, buf) == 0) {
                    entries[i].count++;
                    break;
                }
            }
        }
    }
    
    // Sort by word
    qsort(entries, num_entries, sizeof(Entry), compare);
    
    for (int i = 0; i < num_entries; i++) {
        printf("%s %d\n", entries[i].word, entries[i].count);
    }
    
    return 0;
}
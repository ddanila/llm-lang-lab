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
            if (len < MAX_WORD_LEN - 1) {
                buf[len++] = (char)tolower((unsigned char)c);
            }
        } else {
            if (len > 0) {
                // Find existing word
                int found = -1;
                for (int i = 0; i < num_entries; i++) {
                    if (strcmp(entries[i].word, buf) == 0) {
                        entries[i].count++;
                        found = i;
                        break;
                    }
                }
                
                // If not found, add new entry to first empty slot
                if (found == -1) {
                    for (int i = 0; i < MAX_WORDS && entries[i].word[0] == '\0'; i++) {
                        strcpy(entries[i].word, buf);
                        entries[i].count = 1;
                        num_entries = i + 1;
                        break;
                    }
                }
                
                len = 0;
            }
        }
    }
    
    // Handle last word if any
    if (len > 0) {
        int found = -1;
        for (int i = 0; i < num_entries; i++) {
            if (strcmp(entries[i].word, buf) == 0) {
                entries[i].count++;
                found = i;
                break;
            }
        }
        
        // If not found, add new entry to first empty slot
        if (found == -1) {
            for (int i = num_entries; i < MAX_WORDS && entries[i].word[0] == '\0'; i++) {
                strcpy(entries[i].word, buf);
                entries[i].count = 1;
                num_entries = i + 1;
                break;
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
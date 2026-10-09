#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 10000

typedef struct {
    char word[MAX_LEN];
    int count;
} Entry;

Entry* entries;
int num_entries;

int compare(const void *a, const void *b) {
    return strcmp(((Entry*)a)->word, ((Entry*)b)->word);
}

int main(void) {
    char buf[MAX_LEN];
    size_t len = 0;
    
    int c;
    while ((c = getchar()) != EOF && len < MAX_LEN - 1) {
        if (isalpha((unsigned char)c)) {
            buf[len++] = (char)tolower((unsigned char)c);
        } else {
            if (len > 0) {
                Entry *entry;
                for (int i = 0; i < num_entries; i++) {
                    if (strcmp(entries[i].word, buf) == 0) {
                        entries[i].count++;
                        break;
                    }
                }
                int idx = -1;
                for (int i = 0; i < num_entries; i++) {
                    if (entries[i].word[0] == '\0') {
                        idx = i;
                        break;
                    }
                }
                if (idx == -1) {
                    Entry *e = malloc(sizeof(Entry));
                    strcpy(e->word, buf);
                    e->count = 1;
                    entries[num_entries++] = *e;
                } else {
                    entry = &entries[idx];
                    entry->count++;
                }
                
                // Rebuild entries array to remove empty slots and keep compact
                int j = 0;
                for (int k = 0; k < num_entries; k++) {
                    if (entries[k].word[0] != '\0') {
                        strcpy(entries[j].word, entries[k].word);
                        entries[j].count = entries[k].count;
                        j++;
                    }
                }
                num_entries = j;
                
                // Shift remaining words to fill gaps after removal
                for (int k = 0; k < MAX_LEN - 1; k++) {
                    buf[k] = '\0';
                }
            }
            len = 0;
        }
    }
    
    if (len > 0) {
        Entry *entry;
        for (int i = 0; i < num_entries; i++) {
            if (strcmp(entries[i].word, buf) == 0) {
                entries[i].count++;
                break;
            }
        }
        
        int idx = -1;
        for (int i = 0; i < num_entries; i++) {
            if (entries[i].word[0] == '\0') {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            Entry *e = malloc(sizeof(Entry));
            strcpy(e->word, buf);
            e->count = 1;
            entries[num_entries++] = *e;
        } else {
            entry = &entries[idx];
            entry->count++;
        }
        
        int j = 0;
        for (int k = 0; k < num_entries; k++) {
            if (entries[k].word[0] != '\0') {
                strcpy(entries[j].word, entries[k].word);
                entries[j].count = entries[k].count;
                j++;
            }
        }
        num_entries = j;
    }
    
    qsort(entries, num_entries, sizeof(Entry), compare);
    
    for (int i = 0; i < num_entries; i++) {
        printf("%s %d\n", entries[i].word, entries[i].count);
    }
    
    return 0;
}
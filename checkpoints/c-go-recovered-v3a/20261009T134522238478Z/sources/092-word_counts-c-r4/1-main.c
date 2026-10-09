#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_BYTES 10000
#define HASH_SIZE 10007

typedef struct {
    char word[10005];
    int count;
} Entry;

static Entry entries[HASH_SIZE];
static int entry_count = 0;

int hash(const char *word) {
    unsigned long h = 0;
    for (const char *p = word; *p; p++) {
        h = h * 31 + (unsigned char)*p;
    }
    return (int)(h % HASH_SIZE);
}

void add_entry(const char *word) {
    int h = hash(word);
    for (int i = 0; i < entry_count; i++) {
        if (strcmp(entries[i].word, word) == 0) {
            entries[i].count++;
            return;
        }
        if (entries[i].word[0] == '\0') {
            strcpy(entries[i].word, word);
            entries[i].count = 1;
            return;
        }
    }
}

int main(void) {
    char buffer[MAX_BYTES];
    int len = 0;
    
    while (len < MAX_BYTES && getchar() != EOF) {
        buffer[len++] = getchar();
    }
    
    if (len == 0) return 0;
    
    char *p = buffer;
    char current_word[10005] = {0};
    int current_len = 0;
    
    while (*p) {
        unsigned char c = (unsigned char)*p;
        
        if (isalpha(c)) {
            current_word[current_len++] = tolower(c);
        } else {
            if (current_len > 0) {
                current_word[current_len] = '\0';
                add_entry(current_word);
                current_len = 0;
            }
        }
        p++;
    }
    
    if (current_len > 0) {
        current_word[current_len] = '\0';
        add_entry(current_word);
    }
    
    Entry sorted[entry_count];
    int sorted_count = 0;
    
    for (int i = 0; i < entry_count; i++) {
        if (entries[i].word[0] != '\0') {
            sorted[sorted_count++] = entries[i];
        }
    }
    
    // Bubble sort by word (ascending ASCII order)
    for (int i = 0; i < sorted_count - 1; i++) {
        for (int j = 0; j < sorted_count - i - 1; j++) {
            if (strcmp(sorted[j].word, sorted[j+1].word) > 0) {
                Entry tmp = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = tmp;
            }
        }
    }
    
    for (int i = 0; i < sorted_count; i++) {
        printf("%s %d\n", sorted[i].word, sorted[i].count);
    }
    
    return 0;
}
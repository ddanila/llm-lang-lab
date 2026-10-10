#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char *buf = malloc(10000);
    if (!buf) return 1;
    
    size_t len = fread(buf, 1, 10000, stdin);
    buf[len] = '\0';
    
    typedef struct { char key[10002]; int count; } Entry;
    Entry *entries = NULL;
    size_t n_entries = 0;
    
    const char *p = buf;
    while (*p) {
        if (isalpha((unsigned char)*p)) {
            // Start or continue of a word
            int start = (p == buf || !isalpha((unsigned char)*(p-1)));
            size_t wlen = 0;
            while (p[wlen] && isalpha((unsigned char)p[wlen])) wlen++;
            
            if (wlen > 0) {
                // Convert to lowercase and store
                char word[10002];
                for (size_t i = 0; i < wlen; i++) {
                    word[i] = (unsigned char)tolower(p[start + i]);
                }
                
                // Check if word exists
                int found = 0;
                for (size_t i = 0; i < n_entries; i++) {
                    size_t match = 0;
                    while (word[match] && word[match] == entries[i].key[match]) match++;
                    if (word[match] == '\0') {
                        entries[i].count++;
                        found = 1;
                        break;
                    }
                }
                
                if (!found) {
                    // Insert in sorted order
                    int ins_idx = n_entries;
                    for (size_t i = 0; i < n_entries; i++) {
                        size_t match = 0;
                        while (word[match] && word[match] == entries[i].key[match]) match++;
                        if (word[match] != '\0') { // word > entries[i].key
                            ins_idx = (int)i;
                            break;
                        }
                    }
                    
                    if ((size_t)ins_idx < n_entries) {
                        // Shift elements to make room
                        for (size_t i = n_entries - 1; i > (size_t)ins_idx; i--) {
                            entries[i] = entries[i-1];
                        }
                        entries[ins_idx].key[0] = word[0];
                        for (size_t i = 1; word[i] != '\0'; i++) {
                            entries[ins_idx].key[i] = word[i];
                        }
                        entries[ins_idx].count = 1;
                    } else {
                        // Append at end
                        size_t key_len = wlen;
                        for (size_t i = 0; i < key_len; i++) {
                            entries[n_entries].key[i] = word[i];
                        }
                        entries[n_entries].key[key_len] = '\0';
                        entries[n_entries].count = 1;
                    }
                    n_entries++;
                }
            }
        } else if (p == buf || !isalpha((unsigned char)*(p-1))) {
            // Non-alpha character, potential end of word
            // Just continue scanning
        }
        
        p++;
    }
    
    // Output sorted entries
    for (size_t i = 0; i < n_entries; i++) {
        printf("%s %d\n", entries[i].key, entries[i].count);
    }
    
    free(buf);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    unsigned char buf[5001];
    size_t len = 0;
    int c;
    
    while ((c = getchar()) != EOF) {
        if (len < 5000) {
            buf[len++] = (unsigned char)c;
        }
    }
    
    // Parse the CSV record and compute field lengths
    size_t nfields = 0;
    size_t *f_ends = NULL;
    int in_quotes = 0;
    size_t pos = 0;  // Start position of current field
    
    while (pos < len) {
        unsigned char ch = buf[pos];
        
        if (in_quotes) {
            if (ch == '"') {
                // Check for escaped quote
                if (pos + 1 < len && buf[pos+1] == '"') {
                    // Escaped quote, skip both
                    pos += 2;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    pos++;
                }
            } else {
                // Regular character inside quotes
                pos++;
            }
        } else {
            if (ch == ',') {
                nfields++;
                f_ends = realloc(f_ends, sizeof(size_t) * (nfields + 1));
                f_ends[nfields] = pos;
                pos++;  // Move past the comma
            } else if (ch == '\n' || ch == '\r') {
                // End of record
                nfields++;
                f_ends = realloc(f_ends, sizeof(size_t) * (nfields + 1));
                f_ends[nfields] = pos;
                break;
            } else {
                pos++;
            }
        }
    }
    
    // If we didn't encounter a terminator but reached EOF, the last field is still there
    if (pos >= len) {
        nfields++;
        f_ends = realloc(f_ends, sizeof(size_t) * (nfields + 1));
        f_ends[nfields] = len;
    }
    
    // Print number of fields
    printf("%zu", nfields);
    
    for (size_t j = 0; j < nfields; j++) {
        size_t start_pos = (j == 0) ? 0 : f_ends[j - 1] + 1;
        size_t end_pos = f_ends[j];
        printf(" %zu", end_pos - start_pos);
    }
    
    // Free allocated memory
    free(f_ends);
    printf("\n");
    
    return 0;
}
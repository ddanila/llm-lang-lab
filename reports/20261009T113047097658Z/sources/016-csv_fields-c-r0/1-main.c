#include <stdio.h>
#include <stdlib.h>

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
    size_t *f_lengths = NULL;
    int in_quotes = 0;
    size_t pos = 0;
    size_t i = 0;
    
    while (i < len) {
        unsigned char ch = buf[i];
        
        if (in_quotes) {
            if (ch == '"') {
                // Check for escaped quote
                if (i + 1 < len && buf[i+1] == '"') {
                    // Escaped quote, skip both
                    i += 2;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    i++;
                }
            } else {
                // Regular character inside quotes
                i++;
            }
        } else {
            if (ch == ',') {
                nfields++;
                f_lengths = realloc(f_lengths, sizeof(size_t) * (nfields + 1));
                f_lengths[nfields] = pos;
                pos = i + 1;
                // Skip leading spaces for next field? No, spaces are significant.
            } else if (ch == '\n' || ch == '\r') {
                // End of record
                nfields++;
                f_lengths = realloc(f_lengths, sizeof(size_t) * (nfields + 1));
                f_lengths[nfields] = pos;
                break;
            } else {
                i++;
            }
        }
    }
    
    // If we didn't encounter a terminator but reached EOF, the last field is still there
    if (pos > 0 || nfields == 0) {
        nfields++;
        f_lengths = realloc(f_lengths, sizeof(size_t) * (nfields + 1));
        f_lengths[nfields] = pos;
    }
    
    // Print number of fields
    printf("%zu", nfields);
    
    for (size_t j = 0; j < nfields; j++) {
        size_t end_pos = f_lengths[j];
        if (j == 0) {
            // First field ends at the first comma or terminator
            // Actually, we need to find the actual end of each field
            // Let's re-parse more carefully
        }
    }
    
    // Free allocated memory
    free(f_lengths);
    
    return 0;
}
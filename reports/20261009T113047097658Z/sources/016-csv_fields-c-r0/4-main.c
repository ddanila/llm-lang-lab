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
    
    // Parse the CSV record and compute decoded field lengths
    size_t nfields = 0;
    size_t *f_decoded_lengths = NULL;
    
    // First pass: identify field boundaries and count characters in each field
    int in_quotes = 0;
    size_t prev_pos = 0;
    
    while (prev_pos < len) {
        unsigned char ch = buf[prev_pos];
        
        if (in_quotes) {
            if (ch == '"') {
                // Check for escaped quote
                if (prev_pos + 1 < len && buf[prev_pos+1] == '"') {
                    // Escaped quote - counts as 1 character
                    f_decoded_lengths[nfields-1]++;
                    prev_pos += 2;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    prev_pos++;
                }
            } else {
                // Regular character inside quotes - counts as 1
                f_decoded_lengths[nfields-1]++;
                prev_pos++;
            }
        } else {
            if (ch == ',') {
                nfields++;
                f_decoded_lengths = realloc(f_decoded_lengths, sizeof(size_t) * (nfields + 1));
                prev_pos++;  // Move past the comma
            } else if (ch == '\n' || ch == '\r') {
                break;
            } else {
                // Unquoted character - counts as 1
                f_decoded_lengths[nfields]++;
                prev_pos++;
            }
        }
    }
    
    // If we didn't encounter a terminator but reached EOF, the last field is still there
    if (prev_pos >= len) {
        nfields++;
        f_decoded_lengths = realloc(f_decoded_lengths, sizeof(size_t) * (nfields + 1));
    }
    
    // Print number of fields
    printf("%zu", nfields);
    
    for (size_t j = 0; j < nfields; j++) {
        printf(" %zu", f_decoded_lengths[j]);
    }
    
    printf("\n");
    
    // Free allocated memory
    free(f_decoded_lengths);
    
    return 0;
}
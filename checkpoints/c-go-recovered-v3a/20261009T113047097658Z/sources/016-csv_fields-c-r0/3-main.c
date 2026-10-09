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
    
    // Parse the CSV record and compute decoded field lengths
    size_t nfields = 0;
    size_t *f_decoded_lengths = NULL;
    int in_quotes = 0;
    size_t pos = 0;  // Current position in buffer
    
    while (pos < len) {
        unsigned char ch = buf[pos];
        
        if (in_quotes) {
            if (ch == '"') {
                // Check for escaped quote
                if (pos + 1 < len && buf[pos+1] == '"') {
                    // Escaped quote - counts as 1 character in decoded field
                    pos += 2;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    pos++;
                }
            } else {
                // Regular character inside quotes - counts as 1
                pos++;
            }
        } else {
            if (ch == ',') {
                nfields++;
                f_decoded_lengths = realloc(f_decoded_lengths, sizeof(size_t) * (nfields + 1));
                f_decoded_lengths[nfields] = 0;  // placeholder
                pos++;  // Move past the comma
            } else if (ch == '\n' || ch == '\r') {
                // End of record
                nfields++;
                f_decoded_lengths = realloc(f_decoded_lengths, sizeof(size_t) * (nfields + 1));
                f_decoded_lengths[nfields] = 0;  // placeholder
                break;
            } else {
                pos++;
            }
        }
    }
    
    // If we didn't encounter a terminator but reached EOF, the last field is still there
    if (pos >= len) {
        nfields++;
        f_decoded_lengths = realloc(f_decoded_lengths, sizeof(size_t) * (nfields + 1));
        f_decoded_lengths[nfields] = 0;  // placeholder
    }
    
    // Now re-parse to compute decoded lengths for each field
    size_t prev_pos = 0;
    int in_quotes = 0;
    
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
                nfields--;  // Undo the increment, we'll handle this differently
                break;
            } else if (ch == '\n' || ch == '\r') {
                break;
            } else {
                f_decoded_lengths[nfields-1]++;
                prev_pos++;
            }
        }
    }
    
    // Let me rewrite this more carefully
}
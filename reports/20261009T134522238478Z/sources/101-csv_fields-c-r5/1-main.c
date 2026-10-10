#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until newline or EOF
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (n < 5000) {
            buf[n++] = (char)c;
        } else {
            return 1;
        }
    }
    
    // If we got a newline, consume it
    if (c == '\n') {
        while ((c = getchar()) != EOF && c != '\n' && c != '\r');
    }
    
    // Now parse the buffer
    size_t field_count = 0;
    size_t field_lengths[500]; // max 500 fields
    
    size_t i = 0;
    int in_quotes = 0;
    size_t current_len = 0;
    
    while (i < n) {
        char ch = buf[i];
        
        if (in_quotes) {
            if (ch == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i + 1] == '"') {
                    current_len++;
                    i++;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                }
            } else {
                current_len++;
            }
        } else {
            if (ch == ',') {
                // Store previous field length and reset
                if (field_count < 500) {
                    field_lengths[field_count++] = current_len;
                }
                current_len = 0;
            } else if (ch == '"') {
                in_quotes = 1;
            } else {
                current_len++;
            }
        }
        i++;
    }
    
    // Handle last field
    if (field_count < 500) {
        field_lengths[field_count++] = current_len;
    }
    
    // Output results
    for (size_t j = 0; j < field_count; j++) {
        printf("%zu", field_lengths[j]);
        if (j + 1 < field_count) {
            printf(" ");
        }
    }
    printf("\n");
    
    return 0;
}
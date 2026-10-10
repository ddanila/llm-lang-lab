#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until EOF or newline
    int c;
    while ((c = getchar()) != EOF && (c != '\n' && c != '\r')) {
        if (n < 5000) {
            buf[n++] = (char)c;
        }
    }
    
    // Parse the CSV
    char *p = buf;
    int field_count = 0;
    size_t field_lens[128];
    int field_idx = 0;
    
    while (*p != '\0') {
        if (field_idx >= 128) break; // Should not happen with valid input
        
        size_t len = 0;
        
        if (*p == '"') {
            // Quoted field - count characters inside quotes
            p++; // skip opening quote
            while (*p != '\0' && *p != '"') {
                if (*p == '"') {
                    // Escaped quote "" becomes one " in output, so don't increment len
                    p++;
                } else {
                    len++;
                }
            }
            if (*p == '"') {
                p++; // skip closing quote
            }
        } else {
            // Unquoted field - count until comma or end
            while (*p != '\0' && *p != ',') {
                len++;
                p++;
            }
        }
        
        // Skip comma if present (separator between fields)
        if (*p == ',') p++;
        
        field_lens[field_idx] = len;
        field_count++;
        field_idx++;
    }
    
    // Handle empty input as one empty field
    if (field_count == 0) {
        field_count = 1;
        field_lens[0] = 0;
    }
    
    // Print result
    for (int i = 0; i < field_count; i++) {
        if (i > 0) printf(" ");
        printf("%zu", field_lens[i]);
    }
    printf("\n");
    
    return 0;
}
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
        
        if (*p == '"') {
            // Quoted field
            p++; // skip opening quote
            while (*p != '\0' && *p != '"') {
                if (*p == '"') {
                    // Escaped quote
                    p++;
                } else {
                    field_idx++;
                }
            }
            if (*p == '"') {
                p++; // skip closing quote
            }
        } else {
            // Unquoted field
            while (*p != '\0' && *p != ',') {
                field_idx++;
                p++;
            }
        }
        
        if (field_idx > 0) {
            // Skip comma separator
            if (*p == ',') p++;
        }
        
        field_count++;
    }
    
    // Handle empty input as one empty field
    if (field_count == 0) {
        field_count = 1;
    }
    
    // Print result
    for (int i = 0; i < field_count; i++) {
        if (i > 0) printf(" ");
        printf("%zu", field_lens[i]);
    }
    printf("\n");
    
    return 0;
}
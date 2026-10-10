#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until newline or EOF, max 5000 bytes
    int c;
    while ((c = getchar()) != '\n' && c != EOF && n < 5000) {
        buf[n++] = (char)c;
    }
    buf[n] = '\0';
    
    // Handle empty input as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields and collect lengths
    char *p = buf;
    int field_count = 0;
    size_t *field_lengths = NULL;
    
    while (*p != '\0') {
        field_count++;
        
        // Check if field is quoted
        if (*p == '"') {
            p++; // skip opening quote
            size_t field_len = 0;
            
            while (*p != '"') {
                if (*p == '"') {
                    p++; // skip escaped quote (second quote)
                } else {
                    field_len++;
                }
                if (*p == '\0') break;
            }
            
            // After loop, *p should be '"' or '\0'
            if (*p != '"') {
                // Unclosed quote - treat rest as field content
                while (*p != '\0') {
                    field_len++;
                    p++;
                }
            } else {
                p++; // skip closing quote
            }
        } else {
            // Unquoted field
            size_t start = (size_t)(p - buf);
            while (*p != ',' && *p != '\0') {
                p++;
            }
            size_t len = (size_t)(p - buf) - start;
        }
        
        // Allocate or resize array for field lengths
        if (field_lengths == NULL) {
            field_lengths = malloc(field_count * sizeof(size_t));
        } else {
            field_lengths = realloc(field_lengths, field_count * sizeof(size_t));
        }
        field_lengths[field_count - 1] = len;
    }
    
    // Print result
    printf("%d", field_count);
    for (int i = 0; i < field_count; i++) {
        printf(" %zu", field_lengths[i]);
    }
    printf("\n");
    
    free(field_lengths);
    return 0;
}
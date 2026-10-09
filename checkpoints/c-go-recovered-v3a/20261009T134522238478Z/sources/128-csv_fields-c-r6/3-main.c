#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5000

int main(void) {
    char buf[MAX_LEN];
    size_t n = 0;
    
    // Read input until EOF or newline
    int c;
    while ((c = getchar()) != EOF && n < MAX_LEN - 1) {
        if (c == '\n') break;
        buf[n++] = (char)c;
    }
    buf[n] = '\0';
    
    // Parse CSV fields - simple comma-separated parsing
    char *p = buf;
    size_t field_count = 0;
    size_t *field_lens = malloc(MAX_LEN * sizeof(size_t));
    if (!field_lens) return 1;
    
    while (*p != '\0') {
        // Count characters in current field
        size_t len = 0;
        char *end = p;
        
        // Find end of field (comma or null terminator)
        while (*end != '\0' && *(end + 1) != ',') {
            end++;
            len++;
        }
        
        if (field_count < MAX_LEN / 2) {
            field_lens[field_count] = len;
        }
        field_count++;
        
        // Move past comma if present
        if (*end == ',') {
            p = end + 1;
        } else {
            break;
        }
    }
    
    // Check if there's an empty final field (string ends with comma)
    char *last_comma = strrchr(buf, ',');
    if (last_comma != NULL && last_comma[1] == '\0') {
        // There's an empty field after the last comma
        if (field_count < MAX_LEN / 2) {
            field_lens[field_count] = 0;
        }
        field_count++;
    }
    
    // Output result
    printf("%zu", field_count);
    for (size_t i = 0; i < field_count; i++) {
        printf(" %zu", field_lens[i]);
    }
    printf("\n");
    
    free(field_lens);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input into buffer, handling LF and CRLF terminators
    int c;
    while ((c = getchar()) != EOF && (n + 2 < 5000 || c == '\r' || c == '\n')) {
        if (c == '\r') {
            // Check for CRLF
            int next = getchar();
            if (next == '\n') {
                n++;
            }
            break;
        } else if (c == '\n') {
            n++;
            break;
        } else {
            buf[n++] = (char)c;
        }
    }
    
    // Handle empty input as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    int field_count = 0;
    int *field_lengths = NULL;
    
    char *pos = buf;
    
    // Process each field
    while (pos < buf + n) {
        size_t field_len = 0;
        
        // Check if we're at the end of the CSV (newline or EOF without trailing content)
        int done = 0;
        for (char *p = pos; p < buf + n; p++) {
            if (*p == '\n') {
                done = 1;
                break;
            }
        }
        
        // Parse one field
        char *start = pos;
        int in_quotes = 0;
        
        while (pos < buf + n) {
            if (*pos == '"') {
                // Check if this is an escaped quote or delimiter
                if (in_quotes && pos + 1 < buf + n && *(pos + 1) == '"') {
                    // Escaped quote inside quoted field
                    pos += 2;
                } else if (!in_quotes) {
                    // Start of quoted field
                    in_quotes = 1;
                    pos++;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    pos++;
                }
            } else if (*pos == ',') {
                // Field delimiter - only when not inside quotes
                if (!in_quotes) {
                    done = 1;
                    break;
                } else {
                    // Comma inside quotes is literal
                    pos++;
                }
            } else {
                // Regular character
                pos++;
            }
        }
        
        field_len = pos - start;
        
        field_count++;
        int *new_lengths = realloc(field_lengths, (field_count + 1) * sizeof(int));
        if (new_lengths) {
            field_lengths = new_lengths;
            field_lengths[field_count - 1] = (int)field_len;
        }
        
        // If we hit a newline, stop processing fields
        for (char *p = pos; p < buf + n && *p != '\n'; p++);
        if (*pos == '\n') {
            break;
        }
    }
    
    // Output results
    for (int i = 0; i < field_count; i++) {
        printf("%d", field_lengths[i]);
        if (i < field_count - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(field_lengths);
    return 0;
}
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
    
    while (pos < buf + n) {
        int in_quotes = 0;
        size_t field_len = 0;
        
        while (pos < buf + n) {
            if (*pos == '"') {
                // Check if this is an escaped quote (two consecutive quotes) or a delimiter
                if (in_quotes && pos + 1 < buf + n && *(pos + 1) == '"') {
                    // Escaped quote inside quoted field
                    field_len++;
                    pos += 2; // Skip both quotes
                } else if (!in_quotes) {
                    // Start of quoted field
                    in_quotes = 1;
                    field_len++;
                    pos++;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    field_len++;
                    pos++;
                }
            } else if (*pos == ',') {
                // Field delimiter - only when not inside quotes
                if (!in_quotes) {
                    break;
                } else {
                    // Comma inside quotes is literal
                    field_len++;
                    pos++;
                }
            } else {
                // Regular character
                field_len++;
                pos++;
            }
        }
        
        field_count++;
        int *new_lengths = realloc(field_lengths, (field_count + 1) * sizeof(int));
        if (new_lengths) {
            field_lengths = new_lengths;
            field_lengths[field_count - 1] = (int)field_len;
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
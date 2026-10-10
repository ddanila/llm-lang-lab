#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t len = 0;
    int c;

    // Read input until EOF or newline
    while ((c = getchar()) != EOF && (c != '\n' || len > 0)) {
        if (len < sizeof(buf) - 1) {
            buf[len++] = (char)c;
        } else {
            break;
        }
    }
    buf[len] = '\0';

    // Parse CSV and count fields with lengths
    int field_count = 0;
    size_t pos = 0;
    size_t start = 0;
    int in_quotes = 0;
    
    while (pos < len) {
        if (in_quotes) {
            if (buf[pos] == '"') {
                // Check for escaped quote
                if (pos + 1 < len && buf[pos + 1] == '"') {
                    pos += 2; // Skip both quotes
                } else {
                    in_quotes = 0; // End of quoted field
                    pos++;
                }
            } else {
                pos++;
            }
        } else {
            if (buf[pos] == ',') {
                field_count++;
                start = pos + 1;
            } else if (buf[pos] == '"') {
                in_quotes = 1;
            } else {
                // Regular character, continue
            }
        }
    }

    // Handle trailing comma or end of string
    if (start < len) {
        field_count++;
    }

    // Print field count and lengths
    printf("%d", field_count);
    
    for (int i = 0; i <= field_count; i++) {
        size_t field_start = start + i;
        size_t field_end = len;
        
        if (i == field_count) {
            // Last field
            field_end = len;
        } else {
            // Find next comma or end
            for (size_t j = field_start; j < len; j++) {
                if (buf[j] == ',') {
                    field_end = j;
                    break;
                }
            }
        }
        
        size_t field_len = field_end - field_start;
        printf(" %zu", field_len);
    }
    
    printf("\n");
    
    return 0;
}
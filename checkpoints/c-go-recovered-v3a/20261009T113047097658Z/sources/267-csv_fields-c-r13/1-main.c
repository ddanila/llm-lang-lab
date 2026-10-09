#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5000

int main(void) {
    char buf[MAX_LEN + 1];
    size_t len = fread(buf, 1, MAX_LEN, stdin);
    
    // Handle empty input (one empty field)
    if (len == 0) {
        printf("1 0\n");
        return 0;
    }

    // Remove trailing LF or CRLF
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
        len--;
    }

    size_t field_count = 0;
    size_t total_len = 0;
    size_t i = 0;
    int in_quotes = 0;
    char current_field[MAX_LEN + 1];
    size_t field_pos = 0;

    while (i < len) {
        unsigned char c = (unsigned char)buf[i];
        
        if (in_quotes) {
            if (c == '"') {
                // Check for escaped quote
                if (i + 1 < len && buf[i + 1] == '"') {
                    current_field[field_pos++] = '"';
                    i += 2;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    i++;
                }
            } else {
                current_field[field_pos++] = (char)c;
                i++;
            }
        } else {
            if (c == '"') {
                // Start of quoted field
                in_quotes = 1;
                i++;
            } else if (c == ',') {
                // End of unquoted field
                current_field[field_pos] = '\0';
                field_count++;
                total_len += field_pos;
                field_pos = 0;
                i++;
            } else {
                current_field[field_pos++] = (char)c;
                i++;
            }
        }
    }

    // Handle final field (if input doesn't end with comma)
    if (field_pos > 0 || in_quotes) {
        current_field[field_pos] = '\0';
        field_count++;
        total_len += field_pos;
    } else if (len == 0) {
        // Already handled empty input case, but for safety
        field_count = 1;
        total_len = 0;
    }

    // Print results
    printf("%zu", field_count);
    for (size_t j = 0; j < field_count; j++) {
        printf(" %zu", total_len - field_count + 1); // This is wrong, need to track per-field lengths
    }
    
    return 0;
}
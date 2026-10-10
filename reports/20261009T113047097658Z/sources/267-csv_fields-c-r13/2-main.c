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
    char current_field[MAX_LEN + 1];
    size_t field_pos = 0;
    
    for (size_t i = 0; i < len; ) {
        unsigned char c = (unsigned char)buf[i];
        
        if (c == '"') {
            // Check if start of quoted field or escaped quote
            if (i + 1 < len && buf[i + 1] == '"') {
                // Escaped quote in quoted field - continue as quoted
                current_field[field_pos++] = '"';
                i += 2;
            } else {
                // Toggle quoted state
                // If we were not quoted, start quoting (field continues)
                // If we were quoted, end quoting (field ends at comma)
                if (!field_count) {
                    // First field starts with quote
                    in_quotes = 1;
                } else {
                    // Previous field ended, this is a new field starting with quote
                    current_field[field_pos] = '\0';
                    field_count++;
                    field_pos = 0;
                    in_quotes = 1;
                }
                i++;
            }
        } else if (c == ',') {
            // Field separator - end current field
            current_field[field_pos] = '\0';
            field_count++;
            field_pos = 0;
            i++;
        } else {
            current_field[field_pos++] = (char)c;
            i++;
        }
    }

    // Handle final field
    if (field_pos > 0) {
        current_field[field_pos] = '\0';
        field_count++;
    }

    // Print results - need to track lengths properly
    printf("%zu", field_count);
    
    // Need to re-read or store lengths
    return 0;
}
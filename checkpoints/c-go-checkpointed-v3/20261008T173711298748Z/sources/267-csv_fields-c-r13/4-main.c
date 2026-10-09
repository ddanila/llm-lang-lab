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
    char fields[MAX_LEN + 1][MAX_LEN + 1];
    size_t num_fields[MAX_LEN + 1];
    
    int in_quotes = 0;
    size_t current_len = 0;
    
    for (size_t i = 0; i < len; ) {
        unsigned char c = (unsigned char)buf[i];
        
        if (in_quotes) {
            if (c == '"') {
                // Check for escaped quote
                if (i + 1 < len && buf[i + 1] == '"') {
                    fields[field_count][current_len++] = '"';
                    i += 2;
                } else {
                    // End of quoted field - next char must be comma or end
                    in_quotes = 0;
                    i++;
                }
            } else {
                fields[field_count][current_len++] = (char)c;
                i++;
            }
        } else {
            if (c == '"') {
                // Start of quoted field
                in_quotes = 1;
                i++;
            } else if (c == ',') {
                // End of unquoted field
                fields[field_count][current_len] = '\0';
                num_fields[field_count] = current_len;
                field_count++;
                current_len = 0;
                i++;
            } else {
                fields[field_count][current_len++] = (char)c;
                i++;
            }
        }
    }

    // Handle final field (if not ended by comma)
    if (current_len > 0 || in_quotes) {
        fields[field_count][current_len] = '\0';
        num_fields[field_count] = current_len;
        field_count++;
    }

    // Print results with lengths
    printf("%zu", field_count);
    for (size_t j = 0; j < field_count; j++) {
        printf(" %zu", num_fields[j]);
    }
    printf("\n");
    
    return 0;
}
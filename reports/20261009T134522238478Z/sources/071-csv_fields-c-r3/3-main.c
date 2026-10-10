#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned char buf[5001];
    size_t len = 0;
    
    // Read all input (up to newline or EOF)
    int c;
    while ((c = getchar()) != EOF && len < sizeof(buf)) {
        buf[len++] = (unsigned char)c;
    }
    
    // If no characters read, empty input -> 1 field of length 0
    if (len == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Find content length (stop at first newline)
    size_t content_len = len;
    for (size_t i = 0; i < len; i++) {
        if (buf[i] == '\n') {
            content_len = i;
            break;
        }
    }
    
    // Parse CSV
    int field_count = 0;
    size_t pos = 0;
    
    while (pos < content_len) {
        if (buf[pos] == '"') {
            // Quoted field
            field_count++;
            size_t decoded_len = 0;
            pos++; // skip opening quote
            
            while (pos < content_len) {
                if (buf[pos] == '"') {
                    // Check for escaped quote pair
                    if (pos + 1 < content_len && buf[pos + 1] == '"') {
                        decoded_len++; // "" becomes one "
                        pos += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    decoded_len++;
                    pos++;
                }
            }
            
            // Skip the closing quote if present
            if (pos < content_len && buf[pos] == '"') {
                pos++;
            }
            
            printf("%zu", decoded_len);
        } else {
            // Unquoted field
            field_count++;
            size_t start = pos;
            while (pos < content_len && buf[pos] != ',' && buf[pos] != '\n') {
                pos++;
            }
            size_t decoded_len = pos - start;
            printf("%zu", decoded_len);
        }
        
        // Handle delimiter
        if (pos < content_len) {
            if (buf[pos] == ',') {
                pos++;
            } else if (buf[pos] == '\n' || buf[pos] == '\r') {
                break;
            }
        }
    }
    
    printf("\n");
    return 0;
}
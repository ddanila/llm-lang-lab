#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned char buf[5001];
    size_t len = 0;
    
    // Read input until EOF or newline (but keep reading after first newline if there's content before it)
    int c;
    while ((c = getchar()) != EOF && len < sizeof(buf)) {
        buf[len++] = (unsigned char)c;
    }
    
    // If no characters read, empty input -> 1 field of length 0
    if (len == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Find the end position (first newline or EOF)
    size_t content_len = len;
    for (size_t i = 0; i < len; i++) {
        if (buf[i] == '\n') {
            content_len = i;
            break;
        }
    }
    
    // Now parse CSV from buf[0..content_len-1]
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
                    // Check for escaped quote
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
            
            // Print field length
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
        
        // Skip delimiter
        if (pos < content_len) {
            if (buf[pos] == ',') {
                pos++;
            } else if (buf[pos] == '\n') {
                break;
            } else if (buf[pos] == '\r') {
                pos++;
                if (pos < content_len && buf[pos] == '\n') {
                    pos++;
                }
                break;
            }
        }
    }
    
    printf("\n");
    return 0;
}
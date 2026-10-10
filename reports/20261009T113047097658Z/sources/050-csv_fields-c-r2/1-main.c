#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input byte by byte until EOF or newline
    int c;
    while ((c = getchar()) != EOF && c != '\n' && c != '\r') {
        if (n < (size_t)(sizeof(buf) - 1)) {
            buf[n++] = (char)c;
        }
    }
    
    // If no characters read, it's one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse the CSV line
    char *p = buf;
    size_t field_count = 0;
    size_t total_len = 0;
    
    while (*p != '\0') {
        // Count length of current field before comma
        size_t field_len = 0;
        char *comma = NULL;
        
        if (*p == '"') {
            // Quoted field
            p++; // skip opening quote
            while (*p != '"') {
                if (*p == '"') {
                    // Escaped quote: check next char
                    if (p[1] == '"') {
                        p += 2; // skip both quotes, count as one char in field
                    } else {
                        // Unmatched quote - treat as error or end? 
                        // According to spec, this shouldn't happen in valid input
                        break;
                    }
                } else {
                    p++;
                }
            }
            // Skip closing quote
            if (*p == '"') {
                p++;
            }
        } else {
            // Unquoted field - find comma or end
            while (*p != ',' && *p != '\0') {
                p++;
            }
        }
        
        field_len = p - buf; // length from start of buffer to current position
        
        if (*p == ',') {
            p++; // skip comma, next iteration handles rest
            field_count++;
            total_len += field_len;
        } else {
            // End of line reached
            field_count++;
            total_len += field_len;
        }
    }
    
    printf("%zu %zu\n", field_count, total_len);
    return 0;
}
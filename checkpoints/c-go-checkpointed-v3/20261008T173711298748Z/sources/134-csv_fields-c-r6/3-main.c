#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until newline or EOF
    int c;
    while ((c = getchar()) != -1 && c != '\n' && c != '\r') {
        if (n < 5000) {
            buf[n++] = (char)c;
        } else {
            break;
        }
    }
    
    // Handle CRLF - if we saw CR, consume LF if present
    while ((c = getchar()) != -1 && c == '\r') {
        buf[n++] = (char)c;
        if (n < 5000) {
            c = getchar();
            if (c == '\n') {
                buf[n++] = (char)c;
            }
        }
    }
    
    // Parse the CSV record
    int field_count = 0;
    size_t total_len = 0;
    char *p = buf;
    
    while (*p) {
        if (*p == '"') {
            // Quoted field
            p++;
            size_t len = 0;
            while (*p && *p != '"') {
                if (*p == '"') {
                    // Escaped quote: two consecutive quotes become one in decoded field
                    p++;
                    if (*p == '"') {
                        len++;
                        p++;
                    } else {
                        // Not an escaped quote, just a single quote (shouldn't happen in valid CSV)
                        // But we'll count it as-is
                        len++;
                    }
                } else {
                    len++;
                }
                p++;
            }
            // Skip closing quote
            if (*p == '"') p++;
            field_count++;
            total_len += len;
        } else {
            // Unquoted field - read until comma or end of string
            size_t len = 0;
            while (*p && *p != ',') {
                len++;
                p++;
            }
            if (len > 0) {
                field_count++;
                total_len += len;
            } else if (*p == ',') {
                // Empty field before comma
                field_count++;
                total_len += 0;
            }
        }
    }
    
    printf("%d %zu\n", field_count, total_len);
    
    return 0;
}
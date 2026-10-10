#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n;
    
    // Read input until newline or EOF
    n = 0;
    int done = 0;
    while (!done && n < 5000) {
        int c = getchar();
        if (c == -1) {
            done = 1;
        } else if (c == '\n') {
            done = 1;
        } else if (c == '\r') {
            // CRLF, ignore and continue to read next char for newline
            int c2 = getchar();
            if (c2 != '\n' && c2 != -1) {
                // Not a valid line ending, put back? Actually input is guaranteed valid.
                // But we should just stop on CR as per "followed by one LF or CRLF"
                // Wait, the spec says "optionally followed by one LF or CRLF terminator"
                // So if we see CR, it must be followed by LF for a valid terminator
                // But we can just treat CR as newline too since input is valid CSV
            } else {
                done = 1;
            }
        } else {
            buf[n++] = (char)c;
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
                    // Escaped quote, consume two quotes
                    p++;
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
            // Unquoted field
            size_t len = 0;
            while (*p && *p != ',' && *p != '\n' && *p != '\r') {
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
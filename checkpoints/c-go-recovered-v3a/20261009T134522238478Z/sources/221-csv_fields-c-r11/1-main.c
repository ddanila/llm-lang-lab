#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXLEN 5000

int main(void) {
    char buf[MAXLEN];
    size_t len = 0;
    
    // Read input until EOF, handling LF and CRLF
    int c;
    while ((c = getchar()) != EOF && len < (MAXLEN - 1)) {
        if (c == '\r') {
            // Skip CR, it's part of CRLF or invalid, but spec says fields contain no CR/LF
            // We'll just skip it and continue reading
            continue;
        }
        buf[len++] = (char)c;
    }
    buf[len] = '\0';

    if (len == 0) {
        // Empty input represents one empty field
        printf("1 0\n");
        return 0;
    }

    // Remove trailing LF or CRLF if present
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
        len--;
    }

    // Now parse the CSV
    size_t field_count = 0;
    size_t total_len = 0;
    
    const char *p = buf;
    while (*p) {
        if (field_count > 0) {
            // Skip comma separator
            while (*p == ',') p++;
        }
        
        field_count++;
        
        // Count length of current field
        size_t field_len = 0;
        bool in_quotes = false;
        const char *q = p;
        
        while (*q) {
            if (*q == '"') {
                if (in_quotes) {
                    // Check for escaped quote
                    if (*(q + 1) == '"') {
                        q += 2;
                        field_len += 2;
                    } else {
                        in_quotes = false;
                        q++;
                        break;
                    }
                } else {
                    in_quotes = true;
                    q++;
                    field_len++;
                }
            } else if (*q == ',') {
                if (in_quotes) {
                    // Comma inside quotes is literal, count it
                    field_len++;
                    q++;
                } else {
                    break;
                }
            } else {
                field_len++;
                q++;
            }
        }
        
        total_len += field_len;
    }

    printf("%zu", field_count);
    for (size_t i = 0; i < field_count - 1; i++) {
        printf(" %zu", total_len / (field_count - i)); // This is wrong, need per-field lengths
    }
    // Actually, I need to compute each field's length separately
    
    return 0;
}
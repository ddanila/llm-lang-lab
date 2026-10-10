#include <stdio.h>
#include <string.h>

#define MAXLEN 5000

int main(void) {
    char buf[MAXLEN];
    size_t len = 0;
    
    // Read input until EOF, handling LF and CRLF
    int c;
    while ((c = getchar()) != EOF && len < (MAXLEN - 1)) {
        if (c == '\r') {
            continue;
        }
        buf[len++] = (char)c;
    }
    buf[len] = '\0';

    // Remove trailing LF or CRLF if present
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
        len--;
    }

    // Handle empty input case
    if (len == 0) {
        printf("1 0\n");
        return 0;
    }

    // Parse CSV and compute field lengths
    size_t field_count = 0;
    const char *p = buf;
    
    while (*p) {
        if (field_count > 0) {
            // Skip comma separator
            while (*p == ',') p++;
        }
        
        field_count++;
        
        // Count length of current field
        size_t field_len = 0;
        int in_quotes = 0;
        const char *q = p;
        
        while (*q) {
            if (*q == '"') {
                if (in_quotes) {
                    // Check for escaped quote
                    if (*(q + 1) == '"') {
                        q += 2;
                        field_len += 2;
                    } else {
                        in_quotes = 0;
                        q++;
                        break;
                    }
                } else {
                    in_quotes = 1;
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
        
        printf(" %zu", field_len);
    }
    
    // Print final newline
    printf("\n");
    
    return 0;
}
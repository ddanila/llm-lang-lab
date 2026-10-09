#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;

    // Read input until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF) {
        if (n < sizeof(buf) - 1) {
            buf[n++] = (char)c;
        } else {
            break;
        }
    }
    buf[n] = '\0';

    // Handle empty input case
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    int field_count = 0;
    size_t total_len = 0;
    char *p = buf;

    while (*p != '\0') {
        // Skip leading spaces for first field only (but count them)
        if (field_count == 0 && *p == ' ') {
            // Count leading space as part of the field
            total_len++;
            p++;
            continue;
        }

        size_t len = 0;
        
        // Check if field is quoted
        if (*p == '"') {
            // Quoted field: skip opening quote, count until closing quote
            p++; // skip opening quote
            while (*p != '"') {
                if (*p == '"') {
                    // Escaped quote - count as 1 character (will be decoded to one quote)
                    total_len++;
                    p++;
                    continue;
                }
                len++;
                p++;
            }
            // Skip closing quote
            if (*p == '"') {
                p++;
            }
        } else {
            // Unquoted field: count until comma or end
            while (*p != ',' && *p != '\0') {
                len++;
                p++;
            }
        }
        
        total_len += len;
        field_count++;
        
        // Skip comma if present
        if (*p == ',') {
            p++;
        }
    }

    printf("%d %zu\n", field_count, total_len);
    return 0;
}
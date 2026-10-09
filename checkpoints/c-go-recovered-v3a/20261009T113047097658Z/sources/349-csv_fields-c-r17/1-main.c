#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    // Remove trailing newline(s) for parsing purposes
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        n--;
    }

    size_t fcount = 0;
    size_t total_len = 0;
    char *p = buf;
    size_t i = 0;
    
    while (i < n) {
        // Skip leading spaces for unquoted field
        if (*p == ' ') {
            // This shouldn't happen at start of field, but skip
            p++;
            i++;
            continue;
        }

        if (*p == '"') {
            // Quoted field
            fcount++;
            size_t len = 0;
            p++; // skip opening quote
            while (1) {
                if (*p == '"' && *(p+1) == '"') {
                    // Escaped quote
                    len += 2; // count both quotes as literal in decoded field
                    p += 2;
                } else if (*p == '"') {
                    // End of quoted field
                    break;
                } else {
                    len++;
                    p++;
                }
            }
            total_len += len;
        } else {
            // Unquoted field
            fcount++;
            while (i < n && *p != ',') {
                if (*p == '\n' || *p == '\r') break; // Should not happen per spec
                p++;
                i++;
                total_len++;
            }
        }

        if (*p == ',') {
            p++;
            i++;
        } else if (i < n && *p == ' ') {
            // Leading space for next field - handled in next iteration
        }
    }

    printf("%zu %zu\n", fcount, total_len);
    return 0;
}
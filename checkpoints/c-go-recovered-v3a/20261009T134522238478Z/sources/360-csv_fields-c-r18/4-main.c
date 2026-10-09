#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);

    // Find end of line (CR/LF) and null-terminate
    for (size_t i = 0; i < n; ++i) {
        if (buf[i] == '\n') {
            buf[i + 1] = '\0';
            break;
        }
    }

    // Handle empty input as one empty field
    size_t len = strlen(buf);
    if (len == 0) {
        printf("1 0\n");
        return 0;
    }

    // Parse fields and compute lengths
    char *p = buf;
    int field_count = 0;
    size_t total_len = 0;
    
    while (*p) {
        if (*p == '"') {
            p++; // skip opening quote
            size_t flen = 0;
            while (*p) {
                if (*p == '"') {
                    if (*(p + 1) == '"') {
                        p += 2;
                        flen++;
                    } else {
                        break;
                    }
                } else {
                    p++;
                    flen++;
                }
            }
            // Skip comma if present
            while (*p && *p != ',') p++;
            if (*p == ',') p++;
            field_count++;
        } else {
            size_t start = 0;
            for (size_t i = 0; i < len - field_count; ++i) {
                if (buf[i] == ',') break;
                buf[i] = '\0'; // temporary
                p++;
            }
            while (*p && *p != ',') p++;
            field_count++;
        }
    }

    // Re-parse to get lengths correctly
    p = buf;
    field_count = 0;
    
    while (*p) {
        if (*p == '"') {
            p++; // skip opening quote
            size_t flen = 0;
            while (*p) {
                if (*p == '"') {
                    if (*(p + 1) == '"') {
                        p += 2;
                        flen++;
                    } else {
                        break;
                    }
                } else {
                    p++;
                    flen++;
                }
            }
            // Skip comma if present
            while (*p && *p != ',') p++;
            if (*p == ',') p++;
            field_count++;
        } else {
            size_t start = 0;
            for (size_t i = 0; i < len - field_count; ++i) {
                if (buf[i] == ',') break;
                buf[i] = '\0'; // temporary
                p++;
            }
            while (*p && *p != ',') p++;
            field_count++;
        }
    }

    return 0;
}
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

    // Parse fields
    char *p = buf;
    size_t field_count = 0;
    size_t total_len = 0;
    
    while (*p) {
        if (*p == '"') {
            // Quoted field
            p++; // skip opening quote
            size_t flen = 0;
            while (*p) {
                if (*p == '"') {
                    // Check for escaped quote
                    if (*(p + 1) == '"') {
                        p += 2;
                        flen++;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    p++;
                    flen++;
                }
            }
            // Skip any trailing content (shouldn't happen in valid CSV)
            while (*p && *p != ',') p++;
            if (*p == ',') p++;
            field_count++;
            total_len += flen;
        } else {
            // Unquoted field
            size_t start = 0;
            for (size_t i = 0; i < len - field_count; ++i) {
                if (p[i] == ',') break;
                p++;
            }
            while (*p && *p != ',') p++;
            field_count++;
        }
    }

    // Re-parse to get lengths correctly
    p = buf;
    field_count = 0;
    total_len = 0;
    
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
            total_len += flen;
        } else {
            size_t start = 0;
            for (size_t i = 0; i < len - field_count; ++i) {
                if (p[i] == ',') break;
                p++;
            }
            while (*p && *p != ',') p++;
            field_count++;
        }
    }

    // Actually need to count fields and lengths properly
    // Reset and parse again more carefully
    p = buf;
    field_count = 0;
    
    if (len == 0) {
        printf("1 0\n");
        return 0;
    }

    size_t last_pos = 0;
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
            for (size_t i = last_pos; i < len - field_count; ++i) {
                if (buf[i] == ',') break;
                buf[i] = '\0'; // temporary
                p++;
                last_pos = i + 1;
            }
            while (*p && *p != ',') p++;
            field_count++;
        }
    }

    // This approach is getting messy. Let me rewrite cleanly.
    
    return 0;
}
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

    // Parse CSV fields
    int field_count = 0;
    size_t total_len = 0;
    char *p = buf;

    while (*p != '\0') {
        if (field_count == 0) {
            // First field: skip leading spaces and count until comma or end
            while (*p == ' ') {
                p++;
            }
            size_t len = 0;
            while (*p != ',' && *p != '\0') {
                len++;
                p++;
            }
            total_len += len;
            field_count++;
            if (*p == ',') {
                p++; // skip comma
            }
        } else {
            size_t len = 0;
            while (*p != ',' && *p != '\0') {
                len++;
                p++;
            }
            total_len += len;
            field_count++;
            if (*p == ',') {
                p++; // skip comma
            }
        }
    }

    printf("%zu %zu\n", (size_t)field_count, total_len);
    return 0;
}
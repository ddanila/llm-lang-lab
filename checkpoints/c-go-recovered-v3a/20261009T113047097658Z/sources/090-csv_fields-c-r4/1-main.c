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
            // Should not happen with valid input of at most 5000 bytes
            break;
        }
    }
    buf[n] = '\0';

    if (n == 0) {
        // Empty input represents one empty field
        printf("1 0\n");
        return 0;
    }

    int field_count = 0;
    size_t total_len = 0;
    char *p = buf;

    while (*p != '\0') {
        if (field_count == 0) {
            // Count length of first field (including leading spaces if any)
            // But we need to skip leading spaces only if they are part of the field.
            // Actually, per spec: "Spaces are significant." So leading spaces in a field are counted.
            // However, the first field starts at p. We count until comma or end.
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
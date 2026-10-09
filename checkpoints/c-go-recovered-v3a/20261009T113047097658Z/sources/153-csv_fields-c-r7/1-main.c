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

    // Remove trailing newline(s) from the buffer for processing
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        n--;
    }

    int field_count = 0;
    size_t total_len = 0;

    // Process fields
    for (size_t i = 0; i < n; ) {
        if (buf[i] == '"') {
            // Quoted field
            field_count++;
            size_t len = 0;
            size_t j = i + 1;
            while (j < n) {
                if (buf[j] == '"') {
                    if (j + 1 < n && buf[j+1] == '"') {
                        // Escaped quote
                        len++;
                        j += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    len++;
                    j++;
                }
            }
            i = j + 1;
            total_len += len;
        } else {
            // Unquoted field (until comma)
            field_count++;
            size_t len = 0;
            while (i < n && buf[i] != ',') {
                len++;
                i++;
            }
            if (buf[i] == ',') {
                i++; // skip comma
            }
            total_len += len;
        }
    }

    // Handle empty input as one empty field
    if (field_count == 0 && n > 0) {
        printf("1 %zu\n", total_len);
    } else {
        printf("%d", field_count);
        for (size_t k = 0; k < total_len; k++) {
            // Just print the count of bytes per field
            // We need to track each field's length separately
        }
    }

    return 0;
}
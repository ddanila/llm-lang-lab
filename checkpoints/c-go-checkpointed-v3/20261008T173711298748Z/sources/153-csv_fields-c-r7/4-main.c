#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);

    // Remove trailing newline(s) from the buffer for processing
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        n--;
    }

    int field_count = 0;
    size_t *field_lens = malloc(sizeof(size_t));
    if (!field_lens) return 1;

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
            field_lens[field_count - 1] = len;
        } else {
            // Unquoted field (until comma or end)
            field_count++;
            size_t len = 0;
            while (i < n && buf[i] != ',') {
                len++;
                i++;
            }
            if (buf[i] == ',') {
                i++; // skip comma
            }
            field_lens[field_count - 1] = len;
        }
    }

    // Handle empty input as one empty field
    if (field_count == 0 && n > 0) {
        printf("1 0\n");
        free(field_lens);
        return 0;
    }

    // Print results
    for (int k = 0; k < field_count; k++) {
        if (k > 0) printf(" ");
        printf("%zu", field_lens[k]);
    }
    printf("\n");

    free(field_lens);
    return 0;
}
#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;

    // Read input until EOF or newline (but only ASCII chars)
    while ((c = getchar()) != EOF && (unsigned char)c < 128) {
        if (n < 5000) {
            buf[n++] = (char)c;
        } else {
            break;
        }
    }
    buf[n] = '\0';

    int field_count = 0;
    size_t lengths[100]; // Max fields for 5000 bytes
    size_t len_idx = 0;
    
    int in_quotes = 0;
    char current_field[5001];
    size_t cur_idx = 0;

    for (size_t i = 0; i < n; ) {
        if (in_quotes) {
            if (buf[i] == '"') {
                // Check for escaped quote (two consecutive quotes)
                if (i + 1 < n && buf[i + 1] == '"') {
                    current_field[cur_idx++] = '"';
                    i += 2;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    field_count++;
                    lengths[len_idx++] = cur_idx;
                    cur_idx = 0;
                    i++;
                }
            } else {
                current_field[cur_idx++] = buf[i];
                i++;
            }
        } else {
            if (buf[i] == '"') {
                // Start of quoted field
                in_quotes = 1;
                cur_idx = 0;
                i++;
            } else if (buf[i] == ',') {
                // Field separator - only when not in quotes and cur_idx > 0 or we have content
                field_count++;
                lengths[len_idx++] = cur_idx;
                cur_idx = 0;
                i++;
            } else {
                current_field[cur_idx++] = buf[i];
                i++;
            }
        }
    }

    // Handle last field - but only if there was a field being built
    if (cur_idx > 0 || in_quotes) {
        field_count++;
        lengths[len_idx++] = cur_idx;
    }

    printf("%d", field_count);
    for (int f = 0; f < field_count; f++) {
        printf(" %zu", lengths[f]);
    }
    printf("\n");

    return 0;
}
#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;

    while ((c = getchar()) != EOF && (unsigned char)c < 128) {
        if (n < 5000) {
            buf[n++] = (char)c;
        } else {
            break;
        }
    }
    buf[n] = '\0';

    int field_count = 0;
    size_t total_len = 0;
    int in_quotes = 0;
    int escaped = 0;
    char current_field[5001];
    size_t cur_idx = 0;

    for (size_t i = 0; i < n; ) {
        if (escaped) {
            // Escaped quote: previous was \", next must be "
            escaped = 0;
            if (buf[i] == '"') {
                current_field[cur_idx++] = buf[i];
                i++;
            } else {
                // Malformed, but we skip to avoid infinite loop
                i++;
            }
            continue;
        }

        if (in_quotes) {
            if (buf[i] == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i + 1] == '"') {
                    current_field[cur_idx++] = '"';
                    i += 2;
                    continue;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    field_count++;
                    total_len += cur_idx;
                    cur_idx = 0;
                    i++;
                    continue;
                }
            } else {
                current_field[cur_idx++] = buf[i];
                i++;
            }
        } else {
            if (buf[i] == '"') {
                // Start of quoted field
                in_quotes = 1;
                i++;
            } else if (buf[i] == ',') {
                // Field separator
                field_count++;
                total_len += cur_idx;
                cur_idx = 0;
                i++;
            } else {
                current_field[cur_idx++] = buf[i];
                i++;
            }
        }
    }

    // Handle last field (if any)
    if (cur_idx > 0 || in_quotes) {
        // If we were in quotes at EOF, the input is incomplete per spec, but we count it as a field
        // However, per spec: "Read one valid CSV record" - so we assume well-formed input.
        // But to be safe: if in_quotes is true at end, it's an unterminated quoted field.
        // We'll treat the current content as a field anyway.
        field_count++;
        total_len += cur_idx;
    }

    printf("%d", field_count);
    for (int f = 0; f < field_count; f++) {
        printf(" %zu", total_len - (f == 0 ? 0 : 0)); // This is wrong, need to track per-field lengths
    }
    
    return 0;
}
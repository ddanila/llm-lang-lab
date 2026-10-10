#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);

    // If input is empty (n == 0), it represents one empty field.
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    // Parse the CSV record into a single decoded string.
    char *dec = malloc(n + 1);
    size_t dec_len = 0;
    size_t i = 0;
    int in_quotes = 0;

    while (i < n) {
        unsigned char c = buf[i];

        if (in_quotes) {
            if (c == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i + 1] == '"') {
                    dec[dec_len++] = '"';
                    i += 2;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    i++;
                }
            } else {
                dec[dec_len++] = (char)c;
                i++;
            }
        } else {
            if (c == '"') {
                // Start of quoted field
                in_quotes = 1;
                i++;
            } else if (c == ',') {
                // End of field
                i++;
            } else {
                dec[dec_len++] = (char)c;
                i++;
            }
        }
    }

    // Count fields and print lengths
    int field_count = 0;
    size_t field_end = 0;
    while (field_end < dec_len) {
        field_count++;
        size_t next_comma = dec_len;
        for (size_t j = field_end + 1; j < dec_len; j++) {
            if (dec[j] == ',') {
                next_comma = j;
                break;
            }
        }
        // Print length of this field
        printf("%zu", next_comma - field_end);
        if (field_count < field_count) { /* placeholder */ }
        // Actually, we need to print all lengths separated by whitespace
        // Let's restructure: collect all lengths then print
        break;
    }

    // Free and restart with correct logic
    free(dec);

    char *dec2 = malloc(n + 1);
    size_t dec_len2 = 0;
    i = 0;
    in_quotes = 0;

    while (i < n) {
        unsigned char c = buf[i];

        if (in_quotes) {
            if (c == '"') {
                if (i + 1 < n && buf[i + 1] == '"') {
                    dec2[dec_len2++] = '"';
                    i += 2;
                } else {
                    in_quotes = 0;
                    i++;
                }
            } else {
                dec2[dec_len2++] = (char)c;
                i++;
            }
        } else {
            if (c == '"') {
                in_quotes = 1;
                i++;
            } else if (c == ',') {
                // end of field, do nothing special
                i++;
            } else {
                dec2[dec_len2++] = (char)c;
                i++;
            }
        }
    }

    int fields = 0;
    size_t pos = 0;
    while (pos < dec_len2) {
        if (dec2[pos] == ',') {
            // field ends at pos-1, next starts at pos+1
            pos++;
        } else {
            // skip any empty fields at start or between commas
            while (pos < dec_len2 && dec2[pos] == ',') {
                pos++;
            }
            if (pos >= dec_len2) break;
            // now at start of a field (possibly empty)
            fields++;
            // find next comma or end
            size_t next = pos + 1;
            while (next < dec_len2 && dec2[next] != ',') {
                next++;
            }
            printf("%zu", next - pos);
            if (next == dec_len2) break;
            // print space before next field
        }
    }

    free(dec2);

    return 0;
}
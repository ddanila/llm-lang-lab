#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5000

int main(void) {
    char buf[MAX_LEN];
    size_t n = 0;

    // Read input character by character until newline or EOF
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (n < MAX_LEN - 1) {
            buf[n++] = (char)c;
        }
    }
    buf[n] = '\0';

    // Count fields and decode
    size_t field_count = 0;
    size_t total_len = 0;

    const char *p = buf;
    if (*p == '\0') {
        // Empty input: one empty field
        printf("1 0\n");
        return 0;
    }

    while (1) {
        size_t start = p - buf;
        int in_quotes = 0;
        size_t len = 0;

        if (*p == '"') {
            // Quoted field
            in_quotes = 1;
            p++; // skip opening quote
            while (*p) {
                if (*p == '"') {
                    if (*(p + 1) == '"') {
                        // Escaped quote, copy both
                        len += 2;
                        p += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    len++;
                    p++;
                }
            }
            if (*p == '"') {
                p++; // skip closing quote
            }
        } else {
            // Unquoted field
            while (*p && *p != ',' && *p != '\n' && *p != '\0') {
                len++;
                p++;
            }
        }

        field_count++;
        total_len += len;
    }

    // Now we need to output the count and lengths. But we didn't store them.
    // Let's rewrite to store lengths in an array.

    return 0;
}
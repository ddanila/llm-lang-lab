#include <stdio.h>
#include <stdlib.h>

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

    // Handle empty input as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    // Count fields and compute lengths
    int len_count = 0;
    size_t current_len = 0;
    int in_quotes = 0;
    size_t pos = 0;

    for (pos = 0; pos < n; pos++) {
        char ch = buf[pos];

        if (in_quotes) {
            if (ch == '"') {
                // Check for escaped quote
                if (pos + 1 < n && buf[pos + 1] == '"') {
                    current_len += 1; // Two quotes become one in decoded output
                    pos++; // Skip the next quote
                } else {
                    in_quotes = 0;
                }
            } else {
                current_len++;
            }
        } else {
            if (ch == ',') {
                len_count++;
                printf(" %zu", current_len);
                current_len = 0;
            } else if (ch == '"') {
                in_quotes = 1;
            } else {
                current_len++;
            }
        }
    }

    // Last field
    len_count++;
    printf(" %zu", current_len);
    printf("\n");

    return 0;
}
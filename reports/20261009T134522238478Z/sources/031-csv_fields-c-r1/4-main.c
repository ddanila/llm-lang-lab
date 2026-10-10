#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;

    while ((c = getchar()) != EOF && (n < 5000)) {
        buf[n++] = (char)c;
    }
    buf[n] = '\0';

    // Find first LF or CRLF to determine actual content length
    size_t len = n;
    for (size_t i = 0; i < n && buf[i] != '\n'; ++i) {
        if (buf[i] == '\r' && i + 1 < n && buf[i+1] == '\n') {
            len = i;
            break;
        } else if (buf[i] == '\n') {
            len = i;
            break;
        }
    }

    int field_count = 0;
    size_t total_len = 0;

    const char *p = buf;
    while (p < p + len) {
        if (*p == '"') {
            ++field_count;
            size_t flen = 0;
            ++p; // skip opening quote
            while (p < p + len && *p != '"') {
                if (*p == '"') {
                    ++p;
                    ++flen;
                } else {
                    ++p;
                    ++flen;
                }
            }
            if (p < p + len) ++p; // skip closing quote
        } else {
            ++field_count;
            size_t flen = 0;
            while (p < p + len && *p != '"') {
                ++p;
                ++flen;
            }
        }

        total_len += flen;
    }

    printf("%d", field_count);
    for (int i = 0; i < field_count - 1; ++i) {
        printf(" ");
    }
    printf("%zu\n", total_len);

    return 0;
}
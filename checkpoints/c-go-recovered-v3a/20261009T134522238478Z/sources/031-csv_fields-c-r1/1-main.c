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
    // If no newline found, the whole buffer is content

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
                    // escaped quote
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
            while (p < p + len && *p != '"') {
                ++p;
            }
        }

        total_len += (*p == '"' ? 1 : 0);
        if (*p == '"') {
            // Count the quotes in the decoded field
            const char *q = buf + (p - buf) - 1; // position of closing quote
            size_t qpos = p - buf;
            while (q >= buf && *q == '"') {
                ++total_len;
                --q;
            }
        } else {
            // Unquoted field: count literal characters
            const char *start = buf + (p - len - 1); // This is wrong
        }
    }

    // Let's rewrite the logic more carefully
}
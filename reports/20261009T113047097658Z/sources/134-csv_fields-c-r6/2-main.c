#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until newline or EOF
    int c;
    while ((c = getchar()) != -1 && c != '\n' && c != '\r') {
        if (n < 5000) {
            buf[n++] = (char)c;
        } else {
            // Buffer full, stop reading
            break;
        }
    }
    
    // Handle CRLF - if we saw CR, consume LF if present
    int got_cr = 0;
    while ((c = getchar()) != -1 && c == '\r') {
        buf[n++] = (char)c;
        got_cr = 1;
        break;
    }
    if (got_cr) {
        // Expecting LF after CR
        int next = getchar();
        if (next == '\n') {
            buf[n++] = (char)next;
        } else if (next != -1) {
            // Unexpected char after CR, but input is valid so this shouldn't happen
            // Just put it back by not consuming it - actually we already consumed it
            // Let's just ignore it for now since input is guaranteed valid
        }
    }
    
    // Parse the CSV record
    int field_count = 0;
    size_t total_len = 0;
    char *p = buf;
    
    while (*p) {
        if (*p == '"') {
            // Quoted field
            p++;
            size_t len = 0;
            while (*p && *p != '"') {
                if (*p == '"') {
                    // Escaped quote, consume two quotes but count as one in decoded field
                    p++;
                    // Skip the next quote too since it's escaped
                    if (*p == '"') {
                        len++;  // Count this as one character in the decoded field
                        p++;
                    }
                } else {
                    len++;
                }
                p++;
            }
            // Skip closing quote
            if (*p == '"') p++;
            field_count++;
            total_len += len;
        } else {
            // Unquoted field
            size_t len = 0;
            while (*p && *p != ',' && *p != '\n' && *p != '\r') {
                len++;
                p++;
            }
            if (len > 0) {
                field_count++;
                total_len += len;
            } else if (*p == ',') {
                // Empty field before comma
                field_count++;
                total_len += 0;
            }
        }
    }
    
    printf("%d %zu\n", field_count, total_len);
    
    return 0;
}
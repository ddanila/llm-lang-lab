#include <stdio.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;
    
    // Read until newline/EOF
    while ((c = getchar()) != -1 && c != '\n') {
        if (c == '\r') continue;  // Ignore CR, treat as line ending marker
        if (n < 5000) buf[n++] = (char)c;
    }
    
    int field_count = 0;
    size_t total_len = 0;
    char *p = buf;
    
    while (*p) {
        if (*p == '"') {
            // Quoted field
            p++;  // skip opening quote
            size_t len = 0;
            while (*p && *p != '"') {
                if (*p == '"') {
                    // Escaped quote - consume both and count as one char
                    p++;
                    if (*p == '"') {
                        len++;
                        p++;
                    } else {
                        // Malformed, but treat as literal
                        len++;
                    }
                } else {
                    len++;
                }
                p++;
            }
            if (*p == '"') p++;  // skip closing quote
            field_count++;
            total_len += len;
        } else {
            // Unquoted field
            size_t len = 0;
            while (*p && *p != ',') {
                len++;
                p++;
            }
            if (len > 0 || *p == ',') {
                field_count++;
                total_len += len;
            }
        }
    }
    
    printf("%d %zu\n", field_count, total_len);
    return 0;
}
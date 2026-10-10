#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;

    // Read input until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF) {
        if (n < 5000) {
            buf[n++] = (char)c;
        } else {
            // Buffer full, ignore extra bytes
        }
    }

    // If input was empty (EOF immediately), treat as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    int field_count = 0;
    size_t *field_lens = NULL;

    char *p = buf;
    size_t len = n;

    // Parse CSV fields
    while (len > 0) {
        if (*p == '"') {
            // Quoted field
            field_count++;
            size_t f_len = 0;
            p++; // skip opening quote
            while (p < buf + len) {
                if (*p == '"') {
                    // Check for escaped quote (two consecutive quotes)
                    if (p + 1 < buf + len && *(p + 1) == '"') {
                        f_len += 2; // literal double quote is two chars in decoded? 
                        // Wait, we need to decode: two quotes become one quote.
                        // But output is length in bytes of each decoded field.
                        // So "a""b" decodes to a"b which is 3 bytes.
                        // So when we see two quotes, it's one char in decoded.
                        p += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    f_len++;
                    p++;
                }
            }
            if (p < buf + len && *p == '"') {
                p++; // skip closing quote
            }
            while (len > 0 && *p != ',') {
                if (*p == '"' || *(p+1) == '"') {
                    // This shouldn't happen after closing quote
                    break;
                }
                p++;
            }
        } else {
            // Unquoted field
            while (len > 0 && *p != ',' && *p != '\n' && *p != '\r') {
                p++;
            }
        }

        // Skip comma if present
        if (len > 0 && *p == ',') {
            p++;
            len--;
        } else {
            // End of fields
            break;
        }
    }

    // This parsing is getting complex. Let me rewrite more carefully.
    
    return 0;
}
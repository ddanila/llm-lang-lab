#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;

    // Read input until EOF or newline (LF or CRLF)
    while ((c = getchar()) != EOF && c != '\n') {
        if (n < 5000) buf[n++] = (char)c;
    }
    buf[n] = '\0';

    if (n == 0) {
        // Empty input -> one empty field
        printf("1 0\n");
        return 0;
    }

    int field_count = 0;
    char *p = buf;
    char *end = buf + n;

    while (p < end) {
        if (*p == '"') {
            // Quoted field
            p++; // skip opening quote
            size_t len = 0;
            while (p < end && *p != '"') {
                if (*p == '"') {
                    // Check for escaped quote (two quotes)
                    if (p + 1 < end && *(p + 1) == '"') {
                        p += 2;
                        len++; // count one field character (the single quote)
                    } else {
                        break; // end of quoted field
                    }
                } else {
                    p++;
                    len++;
                }
            }
            if (p < end && *p == '"') {
                p++; // skip closing quote
            }
            field_count++;
            printf("%zu", len);
        } else {
            // Unquoted field
            size_t len = 0;
            while (p < end && *p != ',' && *p != '\n' && *p != '\r') {
                p++;
                len++;
            }
            field_count++;
            printf("%zu", len);
        }

        if (field_count > 1) printf(" ");

        // Skip comma or newline
        if (*p == ',') {
            p++;
        } else if (*p == '\n' || *p == '\r') {
            break;
        }
    }

    printf("\n");
    return 0;
}
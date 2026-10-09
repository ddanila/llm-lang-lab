#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n;
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 0;
    }
    n = strlen(buf);
    // Remove trailing LF or CRLF if present
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        buf[--n] = '\0';
    }

    char *fields[256];
    int fcount = 0;
    char *p = buf;
    while (*p) {
        fields[fcount++] = p;
        // Parse one field: either unquoted or quoted
        if (*p == '"') {
            // Quoted field
            p++; // skip opening quote
            while (1) {
                if (*p == '"' && *(p+1) == '"') {
                    // escaped quote: copy both quotes and advance by 2
                    p += 2;
                } else if (*p == '"') {
                    // end of quoted field
                    break;
                } else {
                    p++;
                }
            }
            // skip closing quote
            p++;
        } else {
            // Unquoted field: advance until comma or null
            while (*p && *p != ',') {
                p++;
            }
        }
    }

    // Output number of fields
    printf("%d", fcount);
    for (int i = 0; i < fcount; i++) {
        char *f = fields[i];
        size_t len = strlen(f);
        if (i > 0) printf(" ");
        printf("%zu", len);
    }
    printf("\n");

    return 0;
}
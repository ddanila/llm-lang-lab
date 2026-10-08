#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t len = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (len >= 5000) break;
        buf[len++] = (char)c;
    }
    buf[len] = '\0';

    char *p = buf;
    size_t nfields = 0;
    size_t field_lens[256];

    while (*p != '\0') {
        if (nfields >= 255) break;
        
        if (*p == '"') {
            p++;
            size_t qlen = 0;
            while (*p != '"') {
                if (*p == '"' && *(p+1) == '"') {
                    qlen += 2;
                    p += 2;
                } else if (*p == '\n' || *p == '\r') {
                    break;
                } else {
                    qlen++;
                    p++;
                }
            }
            field_lens[nfields] = qlen;
            nfields++;
        } else {
            size_t start = p - buf;
            while (*p != ',' && *p != '\0' && *p != '\n' && *p != '\r') {
                p++;
            }
            field_lens[nfields] = (size_t)(p - buf) - start;
            nfields++;
        }
    }

    if (nfields == 0) nfields = 1;

    printf("%zu", nfields);
    for (size_t i = 0; i < nfields; i++) {
        printf(" %zu", field_lens[i]);
    }
    printf("\n");

    return 0;
}
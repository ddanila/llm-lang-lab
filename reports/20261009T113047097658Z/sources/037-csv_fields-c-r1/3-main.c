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
        
        size_t start = p - buf;
        
        if (*p == '"') {
            p++;  // skip opening quote
            while (*p != '"') {
                if (*p == '"' && *(p+1) == '"') {
                    p += 2;  // skip escaped quote
                } else if (*p == '\n' || *p == '\r') {
                    break;  // unexpected CR/LF in field
                } else {
                    p++;
                }
            }
            if (*p == '"') p++;  // skip closing quote
        } else {
            while (*p != ',' && *p != '\0' && *p != '\n' && *p != '\r') {
                p++;
            }
        }
        
        field_lens[nfields] = (size_t)(p - buf) - start;
        nfields++;
    }

    if (nfields == 0) nfields = 1;

    printf("%zu", nfields);
    for (size_t i = 0; i < nfields; i++) {
        printf(" %zu", field_lens[i]);
    }
    printf("\n");

    return 0;
}
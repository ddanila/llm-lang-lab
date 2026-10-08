#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned char buf[5001];
    int n = 0;
    int c;

    while ((c = getchar()) != EOF && n < 5000) {
        if (c == '\n' || c == '\r') {
            break;
        }
        buf[n++] = (unsigned char)c;
    }

    // Handle empty input as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    int field_count = 0;
    
    unsigned char *p = buf;
    unsigned char *start = buf;
    
    // First pass: count fields and mark boundaries
    while (p < buf + n) {
        if (*p == '"') {
            field_count++;
            p++; // skip opening quote
            while (p < buf + n && *p != '"' || *(p+1) == '"') {
                if (*p == '"') {
                    if (*(p+1) == '"') {
                        p += 2;
                    } else {
                        break;
                    }
                } else {
                    p++;
                }
            }
        } else if (*p == ',') {
            field_count++;
            p++;
        } else {
            break;
        }
    }

    // Second pass: compute lengths
    printf("%d", field_count);
    
    unsigned char *field_start = buf;
    int i = 0;
    while (i < n) {
        if (buf[i] == '"') {
            unsigned char *qstart = &buf[i];
            unsigned char *pp = qstart + 1; // after opening quote
            long fl = 0;
            while (pp < buf + n && *pp != '"' || *(pp+1) == '"') {
                if (*pp == '"') {
                    if (*(pp+1) == '"') {
                        fl += 1; // one decoded char for two quotes
                        pp += 2;
                    } else {
                        break;
                    }
                } else {
                    fl += 1;
                    pp++;
                }
            }
            printf(" %lu", (unsigned long)fl);
            i = (int)(pp - buf);
        } else if (buf[i] == ',') {
            // empty field, length 0
            printf(" 0");
            i++;
        } else {
            break;
        }
    }
    
    // Handle final field after last comma or end of input
    if (field_count > 0 && i < n) {
        unsigned char *qstart = &buf[i];
        unsigned char *pp = qstart + 1;
        long fl = 0;
        while (pp < buf + n && *pp != '"' || *(pp+1) == '"') {
            if (*pp == '"') {
                if (*(pp+1) == '"') {
                    fl += 1;
                    pp += 2;
                } else {
                    break;
                }
            } else {
                fl += 1;
                pp++;
            }
        }
        printf(" %lu", (unsigned long)fl);
    }
    
    printf("\n");
    
    return 0;
}
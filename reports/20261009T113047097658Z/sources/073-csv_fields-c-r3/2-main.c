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
    unsigned long total_len = 0;
    
    unsigned char *p = buf;
    unsigned char *start = buf;
    
    while (p < buf + n) {
        if (*p == '"') {
            field_count++;
            start = p;
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
            start = p + 1;
        } else {
            // This shouldn't happen in valid CSV at start of field
            break;
        }
    }

    // Now calculate lengths for each field
    unsigned char *field_start = buf;
    int i = 0;
    
    while (i < n) {
        if (buf[i] == '"') {
            field_count++;
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
            i = (int)(pp - buf);
        } else if (buf[i] == ',') {
            field_count++;
            // empty field, length 0
            i++;
        } else {
            break;
        }
    }

    printf("%d", field_count);
    
    return 0;
}
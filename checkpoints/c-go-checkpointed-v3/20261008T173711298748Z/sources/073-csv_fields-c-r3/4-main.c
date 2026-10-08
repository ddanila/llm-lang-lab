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
    
    // Process each field
    unsigned char *p = buf;
    while (p < buf + n) {
        if (*p == '"') {
            // Quoted field
            field_count++;
            p++; // skip opening quote
            long fl = 0;
            while (p < buf + n && *p != '"' || *(p+1) == '"') {
                if (*p == '"') {
                    if (*(p+1) == '"') {
                        fl += 1; // escaped quote: """ -> "
                        p += 2;
                    } else {
                        break;
                    }
                } else {
                    fl += 1;
                    p++;
                }
            }
            printf(" %lu", (unsigned long)fl);
        } else if (*p == ',') {
            // Empty field
            field_count++;
            printf(" 0");
            p++;
        } else {
            // Unquoted character (not comma or quote at start of field)
            break;
        }
    }

    // Handle final field after last comma or end of input
    if (field_count > 0 && p < buf + n) {
        long fl = 0;
        while (p < buf + n && *p != '"' || *(p+1) == '"') {
            if (*p == '"') {
                if (*(p+1) == '"') {
                    fl += 1;
                    p += 2;
                } else {
                    break;
                }
            } else {
                fl += 1;
                p++;
            }
        }
        printf(" %lu", (unsigned long)fl);
    }
    
    printf("\n");
    
    return 0;
}
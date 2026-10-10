#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    // Remove trailing newline(s) for parsing purposes
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        n--;
    }

    size_t fcount = 0;
    char *p = buf;
    
    // Print field count first
    printf("%zu", fcount);
    
    while (*p) {
        if (*p == '"') {
            // Quoted field
            fcount++;
            p++; // skip opening quote
            size_t len = 0;
            while (1) {
                if (*p == '"' && *(p+1) == '"') {
                    // Escaped quote - count both quotes as literal
                    len += 2; 
                    p += 2;
                } else if (*p == '"') {
                    // End of quoted field
                    break;
                } else {
                    len++;
                    p++;
                }
            }
        } else {
            // Unquoted field
            fcount++;
            size_t len = 0;
            while (*p != ',' && *p != '\0') {
                if (*p == '\n' || *p == '\r') break; 
                p++;
                len++;
            }
        }

        if (*p == ',') {
            p++;
        } else if (*p == '\0') {
            break;
        } else if (*p == ' ') {
            // Skip leading space before next field
            p++;
        }
    }
    
    printf(" %zu\n", fcount);
    return 0;
}
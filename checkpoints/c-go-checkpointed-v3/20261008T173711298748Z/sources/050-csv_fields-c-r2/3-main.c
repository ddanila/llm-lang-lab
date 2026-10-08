#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input byte by byte until EOF or newline
    int c;
    while ((c = getchar()) != EOF && c != '\n' && c != '\r') {
        if (n < (size_t)(sizeof(buf) - 1)) {
            buf[n++] = (char)c;
        }
    }
    
    // If input is empty, it's one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields and compute decoded lengths
    char *p = buf;
    size_t field_count = 0;
    
    while (*p != '\0') {
        size_t field_len = 0;
        
        if (*p == '"') {
            // Quoted field - count characters excluding the enclosing quotes
            p++; // skip opening quote
            while (*p != '"') {
                if (*p == '"') {
                    // Escaped quote: check next char
                    if (p[1] == '"') {
                        p += 2; // skip both, count as 1 character in decoded field
                        field_len++;
                    } else {
                        break;
                    }
                } else {
                    p++;
                    field_len++;
                }
            }
            // Skip closing quote if present
            if (*p == '"') {
                p++;
            }
        } else {
            // Unquoted field - count until comma or end
            while (*p != ',' && *p != '\0') {
                p++;
                field_len++;
            }
        }
        
        printf("%zu", field_len);
        if (*p == ',') {
            p++; // skip comma
            printf(" ");
            field_count++;
        } else {
            // End of line - print space and finish
            printf(" ");
            field_count++;
        }
    }
    
    printf("\n");
    return 0;
}
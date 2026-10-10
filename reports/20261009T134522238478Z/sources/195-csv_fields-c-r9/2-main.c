#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read up to 5000 bytes, stop at newline or EOF
    int c;
    while ((c = getchar()) != EOF && (n < 5000)) {
        if (c == '\n') break;
        buf[n++] = (char)c;
    }
    
    // Parse CSV fields and count them
    char *p = buf;
    size_t field_count = 0;
    
    // Handle empty input case specially
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    while (*p != '\0') {
        if (*p == ',') {
            field_count++;
            p++;
            continue;
        }
        
        if (*p == '"') {
            // Quoted field
            char *start = p + 1; // after opening quote
            while (*p != '"') {
                if (*(p+1) == '"') {
                    p += 2; // skip escaped quote ""
                    continue;
                }
                p++;
            }
            if (*p == '"') p++; // skip closing quote
            field_count++;
        } else {
            // Unquoted field
            while (*p != ',') {
                p++;
            }
            field_count++;
        }
    }
    
    // Now compute and print lengths for each field
    p = buf;
    printf("%zu", field_count);
    
    while (*p != '\0') {
        if (*p == ',') {
            p++;
            continue;
        }
        
        if (*p == '"') {
            // Quoted field - compute length excluding quotes and escaped quotes
            size_t len = 0;
            p++; // skip opening quote
            while (*p != '"') {
                if (*(p+1) == '"') {
                    len++; // count the escaped quote as 1 char
                    p += 2;
                } else {
                    len++;
                    p++;
                }
            }
            if (*p == '"') p++; // skip closing quote
            printf(" %zu", len);
        } else {
            // Unquoted field
            size_t len = 0;
            while (*p != ',') {
                p++;
                len++;
            }
            printf(" %zu", len);
        }
    }
    printf("\n");
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until newline or EOF
    int c;
    while ((c = getchar()) != EOF && c != '\n' && c != '\r') {
        if (n < 5000) {
            buf[n++] = (char)c;
        }
    }
    
    // If no characters read, it's an empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields and calculate lengths
    size_t num_fields = 0;
    size_t start = 0;
    int in_quotes = 0;
    
    for (size_t i = 0; i < n; i++) {
        unsigned char c = (unsigned char)buf[i];
        
        if (in_quotes) {
            if (c == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i + 1] == '"') {
                    i++;  // Skip next quote
                } else {
                    in_quotes = 0;
                }
            }
        } else {
            if (c == ',') {
                num_fields++;
                start = i + 1;
            } else if (c == '\n' || c == '\r') {
                break;
            }
        }
    }
    
    // Handle last field or only field
    if (num_fields == 0) {
        num_fields = 1;
    } else {
        num_fields++;
    }
    
    // Calculate length of each field
    printf("%zu", num_fields);
    for (size_t f = 0; f < num_fields; f++) {
        size_t len = 0;
        int q = 0;
        
        if (f == 0) {
            for (size_t i = start; i < n; i++) {
                unsigned char c = (unsigned char)buf[i];
                if (q) {
                    if (c == '"') {
                        if (i + 1 < n && buf[i + 1] == '"') {
                            i++;
                        } else {
                            q = 0;
                        }
                    }
                } else {
                    if (c == ',') break;
                    if (c == '\n' || c == '\r') break;
                    len++;
                }
            }
        } else {
            for (size_t i = start; i < n; i++) {
                unsigned char c = (unsigned char)buf[i];
                if (q) {
                    if (c == '"') {
                        if (i + 1 < n && buf[i + 1] == '"') {
                            i++;
                        } else {
                            q = 0;
                        }
                    }
                } else {
                    if (c == ',') break;
                    if (c == '\n' || c == '\r') break;
                    len++;
                }
            }
        }
        
        printf(" %zu", len);
    }
    printf("\n");
    
    return 0;
}
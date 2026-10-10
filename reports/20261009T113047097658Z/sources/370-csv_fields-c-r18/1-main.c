#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until newline or EOF, max 5000 bytes
    int c;
    while ((c = getchar()) != '\n' && c != EOF && n < 5000) {
        buf[n++] = (char)c;
    }
    buf[n] = '\0';
    
    // Handle empty input as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields
    char *p = buf;
    int field_count = 0;
    size_t total_len = 0;
    
    while (*p != '\0') {
        field_count++;
        
        // Check if field is quoted
        if (*p == '"') {
            p++; // skip opening quote
            size_t field_len = 0;
            
            while (*p != '"') {
                if (*p == '"') {
                    p++; // skip escaped quote (second quote)
                } else {
                    field_len++;
                }
                if (*p == '\0') break;
            }
            
            // After loop, *p should be '"' or '\0'
            // If we hit EOF without closing quote, treat as unclosed (but input is valid)
            if (*p != '"') {
                // Unclosed quote - treat rest as field content
                while (*p != '\0') {
                    field_len++;
                    p++;
                }
            } else {
                p++; // skip closing quote
            }
        } else {
            // Unquoted field
            size_t start = (size_t)(p - buf);
            while (*p != ',' && *p != '\0') {
                p++;
            }
            field_len = (size_t)(p - buf) - start;
        }
        
        total_len += field_len;
        
        if (*p == ',') {
            p++; // skip comma
        }
    }
    
    printf("%d", field_count);
    for (int i = 0; i < field_count; i++) {
        // We need to recalculate each field length
        // Let's redo parsing with lengths stored
    }
    
    // Redo parsing to get individual field lengths
    p = buf;
    printf(" ");
    
    while (*p != '\0') {
        size_t field_len = 0;
        
        if (*p == '"') {
            p++; // skip opening quote
            while (*p != '"') {
                if (*p == '"') {
                    p++; // skip escaped quote
                } else {
                    field_len++;
                }
                if (*p == '\0') break;
            }
            if (*p != '"') {
                // unclosed quote - count rest
                while (*p != '\0') {
                    field_len++;
                    p++;
                }
            } else {
                p++; // skip closing quote
            }
        } else {
            // unquoted
            while (*p != ',' && *p != '\0') {
                p++;
            }
            field_len = (size_t)(p - buf) - ((size_t)(buf - buf));
            // Actually need to track start position
        }
        
        printf("%zu", field_len);
        if (*p == ',') {
            p++;
        }
    }
    
    printf("\n");
    return 0;
}
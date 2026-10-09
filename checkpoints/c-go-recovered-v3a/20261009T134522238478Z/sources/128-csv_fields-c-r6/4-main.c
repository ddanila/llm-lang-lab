#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5000

int main(void) {
    char buf[MAX_LEN];
    size_t n = 0;
    
    // Read input until EOF or newline
    int c;
    while ((c = getchar()) != EOF && n < MAX_LEN - 1) {
        if (c == '\n') break;
        buf[n++] = (char)c;
    }
    buf[n] = '\0';
    
    // Parse CSV fields with proper quote handling
    char *p = buf;
    size_t field_count = 0;
    size_t *field_lens = malloc(MAX_LEN * sizeof(size_t));
    if (!field_lens) return 1;
    
    while (*p != '\0') {
        // Check if field is quoted
        if (*p == '"') {
            // Quoted field - count until closing quote (handling escaped quotes)
            size_t len = 0;
            p++; // skip opening quote
            
            while (*p != '\0') {
                if (*p == '"') {
                    // Check for escaped quote (two consecutive quotes)
                    if (*(p + 1) == '"') {
                        len++;  // Count as one character in output
                        p += 2;
                    } else {
                        break;  // End of quoted field
                    }
                } else {
                    len++;
                    p++;
                }
            }
            
            if (field_count < MAX_LEN / 2) {
                field_lens[field_count] = len;
            }
            field_count++;
        } else {
            // Unquoted field - count until comma or end
            size_t len = 0;
            while (*p != '\0' && *(p + 1) != ',') {
                p++;
                len++;
            }
            
            if (field_count < MAX_LEN / 2) {
                field_lens[field_count] = len;
            }
            field_count++;
        }
        
        // Move past comma if present
        if (*p == ',') {
            p++;
        } else {
            break;
        }
    }
    
    // Check if there's an empty final field (string ends with comma)
    char *last_comma = strrchr(buf, ',');
    if (last_comma != NULL && last_comma[1] == '\0') {
        if (field_count < MAX_LEN / 2) {
            field_lens[field_count] = 0;
        }
        field_count++;
    }
    
    // Output result
    printf("%zu", field_count);
    for (size_t i = 0; i < field_count; i++) {
        printf(" %zu", field_lens[i]);
    }
    printf("\n");
    
    free(field_lens);
    return 0;
}
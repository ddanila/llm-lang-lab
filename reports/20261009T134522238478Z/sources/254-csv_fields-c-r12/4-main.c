#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    // Find the end of input (first LF or EOF)
    size_t end = n;
    for (size_t i = 0; i < n; i++) {
        if (buf[i] == '\n') {
            end = i + 1;
            break;
        }
    }
    
    // Handle empty input - should output "1 0"
    if (end == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields from buf[0..end-1]
    char *p = buf;
    size_t field_count = 0;
    size_t *field_lens = malloc(sizeof(size_t) * 500);
    
    while (p < end) {
        if (p >= end) break;
        
        int is_quoted = (*p == '"');
        size_t field_len = 0;
        
        if (is_quoted) {
            p++; // skip opening quote
            while (p < end) {
                if (*p == '"') {
                    if (p + 1 < end && p[1] == '"') {
                        field_len += 2;
                        p += 2;
                    } else {
                        break;
                    }
                } else {
                    field_len++;
                    p++;
                }
            }
        } else {
            while (p < end && *p != ',') {
                field_len++;
                p++;
            }
        }
        
        field_count++;
        size_t *field_lens_arr = realloc(field_lens, sizeof(size_t) * (field_count + 1));
        if (field_lens_arr != NULL) {
            field_lens = field_lens_arr;
            field_lens[field_count - 1] = field_len;
        }
        
        if (p < end && *p == ',') {
            p++;
        }
    }
    
    // Print result
    for (size_t i = 0; i < field_count; i++) {
        if (i > 0) printf(" ");
        printf("%zu", field_lens[i]);
    }
    printf("\n");
    
    free(field_lens);
    return 0;
}
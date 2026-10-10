#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    // Find the end of input (LF or EOF)
    size_t end = n;
    if (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        end = n - 1;
        if (end > 0 && buf[end-1] == '\r') {
            end--;
        }
    }
    
    // Parse CSV fields
    size_t field_count = 0;
    size_t *field_lens = NULL;
    size_t alloc_count = 0;
    size_t len = 0;
    
    size_t i = 0;
    while (i < end) {
        if (buf[i] == '"') {
            // Quoted field
            field_count++;
            len = 0;
            i++;
            while (i < end) {
                if (buf[i] == '"') {
                    if (i + 1 < end && buf[i+1] == '"') {
                        // Escaped quote
                        len++;
                        i += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    len++;
                    i++;
                }
            }
            // Skip comma if present
            if (i < end && buf[i] == ',') {
                i++;
            }
        } else {
            // Unquoted field
            field_count++;
            size_t start = i;
            while (i < end && buf[i] != ',' && buf[i] != '\n' && buf[i] != '\r') {
                i++;
            }
            len = i - start;
            
            // Skip comma if present
            if (i < end && buf[i] == ',') {
                i++;
            }
        }
        
        // Assign len to field_lens
        field_lens[field_count - 1] = len;
    }
    
    // Print result
    printf("%zu", field_count);
    for (size_t j = 0; j < field_count; j++) {
        printf(" %zu", field_lens[j]);
    }
    printf("\n");
    
    free(field_lens);
    return 0;
}
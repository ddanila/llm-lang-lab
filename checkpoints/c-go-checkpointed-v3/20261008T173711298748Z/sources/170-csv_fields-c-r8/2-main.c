#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n;
    
    // Read input with possible CRLF or LF terminator
    n = fread(buf, 1, sizeof(buf), stdin);
    if (n == 0) {
        // Empty input -> one empty field
        printf("1 0\n");
        return 0;
    }
    
    // Remove trailing newline if present
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        n--;
    }
    
    // Now parse the CSV fields from buf[0..n-1]
    size_t out_len = 0;
    char *fields[1024];
    int field_count = 0;
    
    // Parse character by character
    for (size_t i = 0; i < n; ) {
        if (field_count >= 1023) break; // Safety limit
        
        // Skip leading comma for subsequent fields
        if (i > 0 && buf[i] == ',') {
            i++;
            continue;
        }
        
        char *field = malloc(1);
        if (!field) break;
        field[0] = '\0';
        fields[field_count++] = field;
        
        // Check if field is quoted
        if (i < n && buf[i] == '"') {
            i++; // consume opening quote
            size_t j = i;
            while (j < n) {
                if (buf[j] == '"') {
                    // Could be escaped quote or end of field
                    if (j + 1 < n && buf[j+1] == '"') {
                        // Escaped quote: output one quote, advance by 2
                        field[out_len++] = '"';
                        j += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    field[out_len++] = buf[j];
                    j++;
                }
            }
            i = j + 1; // skip closing quote
        } else {
            // Unquoted field: read until comma or end
            size_t k = i;
            while (k < n && buf[k] != ',') {
                field[out_len++] = buf[k];
                k++;
            }
            i = k;
        }
        
        // Terminate this field string
        if (out_len > 0) {
            field[out_len] = '\0';
        } else {
            // Empty unquoted field
            field[0] = '\0';
        }
    }
    
    // Output: number of fields, then length of each field
    printf("%d", field_count);
    for (int i = 0; i < field_count; i++) {
        printf(" %zu", strlen(fields[i]));
    }
    printf("\n");
    
    // Free allocated memory
    for (int i = 0; i < field_count; i++) {
        free(fields[i]);
    }
    
    return 0;
}
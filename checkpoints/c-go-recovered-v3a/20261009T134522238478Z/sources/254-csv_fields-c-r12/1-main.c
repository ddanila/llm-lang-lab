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
    
    // If no newline found and we read something, end is still at the last byte+1
    // But we need to handle empty input specially
    if (end == n && n > 0) {
        // No newline in buffer, but we have data - use full buffer as input
        // Actually, the spec says "optionally followed by one LF or CRLF"
        // So if there's no LF, the whole input is the record
    }
    
    // Parse CSV fields from buf[0..end-1]
    char *p = buf;
    size_t field_count = 0;
    size_t *field_lens = malloc(sizeof(size_t) * 500); // max possible fields
    
    while (p < end) {
        // Check if current position is at end
        if (p == end) break;
        
        // Determine if this field is quoted
        int is_quoted = 0;
        char quote_char = 0;
        
        if (*p == '"') {
            is_quoted = 1;
            p++; // skip opening quote
            quote_char = '"';
        }
        
        size_t field_len = 0;
        int escaped = 0;
        
        while (p < end) {
            if (is_quoted) {
                if (*p == '"') {
                    // Check for escaped quote ("")
                    if (p + 1 < end && p[1] == '"') {
                        field_len++;
                        p += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    field_len++;
                    p++;
                }
            } else {
                // Unquoted field - any character is valid except comma, newline, CR
                // But we already know there's no LF/CR in unquoted fields per spec
                if (*p == ',') {
                    break;
                } else {
                    field_len++;
                    p++;
                }
            }
        }
        
        field_count++;
        size_t *field_lens_arr = realloc(field_lens, sizeof(size_t) * (field_count + 1));
        if (field_lens_arr != NULL) {
            field_lens = field_lens_arr;
            field_lens[field_count - 1] = field_len;
        }
        
        // Skip comma if present (it should be at p now for unquoted, or we broke on quote)
        if (*p == ',') {
            p++;
        } else if (is_quoted && *p != '"') {
            // This shouldn't happen - we should have broken on closing quote
            // But let's handle the case where we're at end without comma
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
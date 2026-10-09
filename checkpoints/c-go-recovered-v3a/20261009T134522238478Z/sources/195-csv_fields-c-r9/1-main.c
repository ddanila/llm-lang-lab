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
    
    // Parse CSV fields
    char *p = buf;
    size_t field_count = 0;
    size_t total_len = 0;
    
    while (*p != '\0' || p == buf) {
        // Skip leading spaces? No, spaces are significant.
        // But we need to handle empty fields.
        // An empty field is when we have consecutive commas or start/end with comma logic.
        
        // Check if current position is at a comma or end
        int has_content = 0;
        
        if (*p == ',') {
            // Empty field before this comma
            field_count++;
            total_len += 0;
            p++;
            continue;
        }
        
        // Check for unquoted field (no quotes at start)
        if (*p != '"') {
            // Unquoted field: read until comma or end
            char *start = p;
            while (*p != ',' && *p != '\0') {
                p++;
            }
            size_t len = (size_t)(p - start);
            field_count++;
            total_len += len;
            if (*p == ',') p++; // skip comma
            continue;
        }
        
        // Quoted field: read until closing quote
        char *start = p;
        p++; // skip opening quote
        
        while (*p != '"') {
            if (*p == '\0') break; // malformed, but input is valid per spec
            // Escape sequence: "" -> "
            if (*(p+1) == '"') {
                // Skip the escaped quote
                p += 2;
                continue;
            }
            p++;
        }
        
        if (*p == '"') {
            p++; // skip closing quote
        } else {
            // No closing quote found, but input is valid so this shouldn't happen
        }
        
        size_t len = (size_t)(p - start);
        field_count++;
        total_len += len;
    }
    
    printf("%zu", field_count);
    for (char *field = buf; *field != '\0'; ) {
        if (*field == ',') {
            field++;
            continue;
        }
        if (*field == '"') {
            // Quoted field
            size_t len = 0;
            char *qstart = field;
            field++; // skip opening quote
            while (*field != '"') {
                if (*(field+1) == '"') {
                    field += 2; // escaped quote, count as 1 char in output
                    continue;
                }
                len++;
                field++;
            }
            if (*field == '"') field++; // skip closing quote
            printf(" %zu", len);
        } else {
            // Unquoted field
            size_t len = 0;
            char *qstart = field;
            while (*field != ',') {
                field++;
                len++;
            }
            printf(" %zu", len);
        }
    }
    printf("\n");
    
    return 0;
}
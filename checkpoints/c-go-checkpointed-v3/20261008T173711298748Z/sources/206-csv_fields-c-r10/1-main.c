#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buffer[5001];
    size_t n;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    
    n = strlen(buffer);
    
    // Remove trailing newline characters (LF or CRLF)
    while (n > 0 && (buffer[n-1] == '\n' || buffer[n-1] == '\r')) {
        buffer[--n] = '\0';
    }
    
    if (n == 0) {
        // Empty input represents one empty field
        printf("1 0\n");
        return 0;
    }
    
    size_t field_count = 0;
    size_t i = 0;
    int in_quotes = 0;
    
    while (i < n) {
        char c = buffer[i];
        
        if (in_quotes) {
            if (c == '"') {
                // Check for escaped quote (two consecutive quotes)
                if (i + 1 < n && buffer[i+1] == '"') {
                    i += 2; // Skip both quotes, count as one field char
                    continue;
                } else {
                    in_quotes = 0; // End of quoted section
                }
            } else {
                i++;
            }
        } else {
            if (c == '"') {
                in_quotes = 1;
                i++;
            } else if (c == ',') {
                field_count++;
                i++;
            } else {
                i++;
            }
        }
    }
    
    // Last field ends at the end of buffer
    field_count++;
    
    printf("%zu", field_count);
    
    for (size_t f = 0; f < field_count; f++) {
        size_t start = i;
        
        if (f > 0) {
            // Skip comma and any spaces before next field? No, spaces are significant
            // But we need to find the start of this field
            while (i < n && buffer[i] == ' ') {
                i++;
            }
        }
        
        if (f == 0) {
            // Skip leading spaces for first field
            while (start < i && buffer[start] == ' ') {
                start++;
            }
        }
        
        size_t len = 0;
        int current_in_quotes = 0;
        size_t j = start;
        
        if (f > 0) {
            // Find the end of previous field (comma)
            while (j < n && buffer[j] != ',') {
                j++;
            }
            i = j + 1; // Move past comma
            
            // Skip spaces after comma
            while (i < n && buffer[i] == ' ') {
                i++;
            }
        }
        
        size_t field_start = i;
        
        if (f > 0) {
            // Skip spaces before this field
            while (i < n && buffer[i] == ' ') {
                i++;
            }
        }
        
        if (buffer[i] == '"') {
            current_in_quotes = 1;
            i++;
            
            while (i < n) {
                char c = buffer[i];
                if (c == '"') {
                    if (i + 1 < n && buffer[i+1] == '"') {
                        i += 2;
                    } else {
                        current_in_quotes = 0;
                        break;
                    }
                } else {
                    i++;
                }
            }
        } else {
            while (i < n && buffer[i] != ',') {
                i++;
            }
        }
        
        len = i - field_start;
        printf(" %zu", len);
    }
    
    printf("\n");
    
    return 0;
}
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
    
    // Parse and decode fields
    size_t field_count = 0;
    size_t i = 0;
    int in_quotes = 0;
    
    // First, count fields by scanning for commas outside quotes
    while (i < n) {
        char c = buffer[i];
        
        if (in_quotes) {
            if (c == '"') {
                // Check for escaped quote (two consecutive quotes)
                if (i + 1 < n && buffer[i+1] == '"') {
                    i += 2; // Skip both quotes, count as one field char
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
    
    // Now decode each field and print its length
    for (size_t f = 0; f < field_count; f++) {
        size_t len = 0;
        
        if (f == 0) {
            // Skip leading spaces for first field
            while (i < n && buffer[i] == ' ') {
                i++;
            }
        } else {
            // Skip comma and any spaces after it
            while (i < n && buffer[i] != ',') {
                i++;
            }
            i++; // Move past comma
            
            // Skip spaces after comma
            while (i < n && buffer[i] == ' ') {
                i++;
            }
        }
        
        if (i >= n) break;
        
        char c = buffer[i];
        
        if (c == '"') {
            in_quotes = 1;
            len++;
            i++;
            
            while (i < n) {
                char ch = buffer[i];
                if (ch == '"') {
                    // Check for escaped quote
                    if (i + 1 < n && buffer[i+1] == '"') {
                        len++; // Count as one field char
                        i += 2;
                    } else {
                        in_quotes = 0;
                        break;
                    }
                } else {
                    len++;
                    i++;
                }
            }
        } else {
            // Unquoted field - count until comma or end
            while (i < n && buffer[i] != ',') {
                len++;
                i++;
            }
        }
        
        printf(" %zu", len);
    }
    
    printf("\n");
    
    return 0;
}
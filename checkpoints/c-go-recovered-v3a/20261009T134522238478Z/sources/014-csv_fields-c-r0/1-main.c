#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 5000

int main(void) {
    char buf[MAX_SIZE];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Remove trailing newline(s)
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        n--;
    }
    
    int field_count = 0;
    size_t total_len = 0;
    bool in_quotes = false;
    size_t i = 0;
    
    while (i < n) {
        char c = buf[i];
        
        if (!in_quotes) {
            if (c == '"') {
                // Start of quoted field
                in_quotes = true;
                field_count++;
                total_len += 1; // count the opening quote
            } else if (c == ',') {
                // End of unquoted field
                field_count++;
                i++; // skip comma
            } else {
                // Regular character
                total_len += 1;
                i++;
            }
        } else {
            if (c == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i+1] == '"') {
                    // Escaped quote: count both and advance by 2
                    total_len += 2;
                    i += 2;
                } else {
                    // End of quoted field
                    in_quotes = false;
                    field_count++;
                    i++; // skip the closing quote
                }
            } else {
                // Regular character inside quotes
                total_len += 1;
                i++;
            }
        }
    }
    
    // Handle final field (if not ended by comma and still in unquoted or quoted state)
    if (i == n) {
        field_count++;
        total_len += (n - i);
    }
    
    printf("%d", field_count);
    for (size_t j = 0; j < total_len; j++) {
        // We need to output the length of each field, not the characters
        // Let me rewrite this properly
    }
    
    return 0;
}
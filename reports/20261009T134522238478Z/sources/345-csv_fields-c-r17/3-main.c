#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until newline or EOF
    int c;
    while ((c = getchar()) != '\n' && c != EOF && n < 5000) {
        buf[n++] = (char)c;
    }
    buf[n] = '\0';
    
    // Handle empty input case
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV and count fields, compute lengths
    int field_count = 0;
    size_t field_len[500]; // max possible fields
    
    int in_quotes = 0;
    size_t current_len = 0;
    size_t i = 0;
    
    while (i < n) {
        char c_char = buf[i];
        
        if (in_quotes) {
            if (c_char == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i+1] == '"') {
                    // Escaped quote, count as one character in decoded field
                    current_len++;
                    i++;
                } else {
                    // End of quoted field - don't count the closing quote
                    in_quotes = 0;
                    // current_len stays as is (doesn't include closing quote)
                }
            } else {
                current_len++;
                i++;
            }
        } else {
            if (c_char == '"') {
                // Start of quoted field - don't count the opening quote
                in_quotes = 1;
                i++;
            } else if (c_char == ',') {
                // End of unquoted field, store length and count
                field_count++;
                field_len[field_count - 1] = current_len;
                current_len = 0;
                i++;
            } else {
                current_len++;
                i++;
            }
        }
    }
    
    // Handle final field (if not ended with comma)
    if (!in_quotes) {
        // If we exited quotes earlier, current_len already has the content
        // If we never entered quotes, current_len is the length of unquoted field
        field_count++;
        field_len[field_count - 1] = current_len;
    } else {
        // Still in quotes at end - this means unclosed quotes or empty quoted field
        // For valid input, if we're still in_quotes and i==n, it could be:
        // 1. Empty quoted field like "" where we've seen the closing quote
        // But our logic would have exited when seeing the single "
        // So this case shouldn't happen with valid input
        // Let's just count current_len as the field
        field_count++;
        field_len[field_count - 1] = current_len;
    }
    
    // Output results
    for (int j = 0; j < field_count; j++) {
        if (j > 0) printf(" ");
        printf("%zu", field_len[j]);
    }
    printf("\n");
    
    return 0;
}
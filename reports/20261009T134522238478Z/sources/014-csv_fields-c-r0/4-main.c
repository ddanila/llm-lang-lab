#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 5000

int main(void) {
    char buf[MAX_SIZE];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    // Remove trailing newline(s)
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        n--;
    }
    
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    int field_count = 0;
    size_t current_len = 0;
    bool in_quotes = false;
    bool field_started = false;
    size_t *field_lengths = NULL;
    
    for (size_t i = 0; i < n; i++) {
        char c = buf[i];
        
        if (!in_quotes) {
            if (c == '"') {
                // Start of quoted field
                in_quotes = true;
                current_len++; // count the opening quote
                field_started = true;
            } else if (c == ',') {
                // End of unquoted field
                field_count++;
                field_lengths = realloc(field_lengths, field_count * sizeof(size_t));
                field_lengths[field_count - 1] = current_len;
                current_len = 0;
                field_started = false;
            } else {
                // Regular character
                current_len++;
            }
        } else {
            if (c == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i+1] == '"') {
                    // Escaped quote: count both and advance by 2
                    current_len += 2;
                    i++;
                } else {
                    // End of quoted field - don't count closing quote
                    in_quotes = false;
                    if (!field_started) {
                        field_count++;
                        field_lengths = realloc(field_lengths, field_count * sizeof(size_t));
                        field_lengths[field_count - 1] = current_len;
                        current_len = 0;
                        field_started = true;
                    }
                }
            } else {
                // Regular character inside quotes
                current_len++;
            }
        }
    }
    
    // Handle final field
    if (current_len > 0 || in_quotes) {
        field_count++;
        field_lengths = realloc(field_lengths, field_count * sizeof(size_t));
        field_lengths[field_count - 1] = current_len;
    } else if (!field_started && field_count == 0) {
        // Empty record case - single empty field
        field_count++;
        field_lengths = realloc(field_lengths, field_count * sizeof(size_t));
        field_lengths[field_count - 1] = 0;
    }
    
    printf("%d", field_count);
    for (int j = 0; j < field_count; j++) {
        printf(" %zu", field_lengths[j]);
    }
    printf("\n");
    
    return 0;
}
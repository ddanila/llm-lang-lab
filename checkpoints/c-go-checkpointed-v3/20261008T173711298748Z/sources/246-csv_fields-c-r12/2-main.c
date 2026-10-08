#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    int c;
    while ((c = getchar()) != EOF && n < (size_t)(sizeof(buf) - 1)) {
        if (c == '\n') {
            break;
        } else if (c == '\r') {
            continue;
        } else {
            buf[n++] = (char)c;
        }
    }
    
    // Parse CSV fields
    int field_count = 0;
    size_t total_len = n;
    
    // Track current field length
    size_t current_field_len = 0;
    size_t prev_field_lens[5001];
    int in_quotes = 0;
    int escaped = 0;
    
    for (size_t pos = 0; pos < total_len; pos++) {
        char ch = buf[pos];
        
        if (escaped) {
            escaped = 0;
            continue;
        }
        
        if (ch == '"') {
            in_quotes = !in_quotes;
            current_field_len++;
        } else if (ch == ',') {
            // End of field
            prev_field_lens[field_count] = current_field_len;
            field_count++;
            current_field_len = 0;
        } else {
            current_field_len++;
        }
    }
    
    // Last field
    prev_field_lens[field_count] = current_field_len;
    field_count++;
    
    if (field_count == 0) {
        // No commas, so one field
        field_count = 1;
    }
    
    printf("%lu", (unsigned long)field_count);
    
    for (int i = 0; i < field_count; i++) {
        printf(" %zu", prev_field_lens[i]);
    }
    printf("\n");
    
    return 0;
}
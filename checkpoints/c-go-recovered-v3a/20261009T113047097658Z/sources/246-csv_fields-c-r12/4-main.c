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
    
    // Handle empty input: one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields
    int field_count = 0;
    size_t current_field_len = 0;
    size_t prev_field_lens[5001];
    int in_quotes = 0;
    int escaped = 0;
    
    for (size_t pos = 0; pos < n; pos++) {
        char ch = buf[pos];
        
        if (escaped) {
            escaped = 0;
            continue;
        }
        
        if (ch == '"') {
            in_quotes = !in_quotes;
            // Don't count quotes in field length for quoted fields
            continue;
        } else if (ch == ',') {
            // End of field - store decoded length
            prev_field_lens[field_count] = current_field_len;
            field_count++;
            current_field_len = 0;
        } else {
            current_field_len++;
        }
    }
    
    // Last field (if there was a comma before, we already counted it)
    // But if the last character is not a comma, we need to add the final field
    if (n > 0 && buf[n-1] != ',') {
        prev_field_lens[field_count] = current_field_len;
        field_count++;
    }
    
    printf("%d", field_count);
    
    for (int i = 0; i < field_count; i++) {
        printf(" %zu", prev_field_lens[i]);
    }
    printf("\n");
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5000

int main(void) {
    char buf[MAX_LEN];
    size_t n = 0;
    
    // Read input until EOF or newline
    int c;
    while ((c = getchar()) != EOF && n < MAX_LEN - 1) {
        if (c == '\n') break;
        buf[n++] = (char)c;
    }
    buf[n] = '\0';
    
    // Parse CSV fields
    char *p = buf;
    size_t field_count = 0;
    size_t *field_lens = malloc((MAX_LEN / 2) * sizeof(size_t));
    if (!field_lens) return 1;
    
    while (*p != '\0') {
        // Find the end of current field (comma or end of string)
        char *end = p;
        while (*end != '\0' && *(end + 1) != ',') {
            end++;
        }
        
        size_t len = end - p;
        if (field_count < MAX_LEN / 2) {
            field_lens[field_count] = len;
        }
        field_count++;
        
        // Move past comma if present
        if (*end == ',') {
            p = end + 1;
        } else {
            break;
        }
    }
    
    // Handle final empty field if string ends with comma
    if (*p == '\0' && field_count > 0) {
        // The loop already handled the last field
        // But we need to check if there's an empty final field
        // If buf ends with ",", then after the comma there's an empty field
        // Actually, let me trace through examples:
        
        // Example 1: "a,\"b,c\",\n" -> fields: "a", "b,c", ""
        // After parsing: p points to '\0' at end, field_count should be 3
        // But the loop breaks when *p == '\0', so we need to check if last char was ','
        
        char *last_comma = strrchr(p - (end == p ? 1 : 0), ',');
        // Hmm, this is getting complicated. Let me simplify.
    }
    
    // Actually, the logic above is wrong. Let me rewrite:
    
    free(field_lens);
    return 0;
}
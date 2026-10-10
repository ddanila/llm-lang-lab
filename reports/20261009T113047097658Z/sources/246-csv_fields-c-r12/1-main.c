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
            // skip CR, expect LF or end
            continue;
        } else {
            buf[n++] = (char)c;
        }
    }
    
    if (n == 0) {
        // Empty input: one empty field
        printf("1 0\n");
        return 0;
    }
    
    size_t pos = 0;
    size_t len = n;
    int in_quotes = 0;
    int escaped = 0;
    size_t field_count = 0;
    long long field_lens[5001]; // store lengths
    
    while (pos < len) {
        char ch = buf[pos++];
        
        if (escaped) {
            escaped = 0;
            continue;
        }
        
        if (ch == '"') {
            in_quotes = !in_quotes;
            continue;
        } else if (ch == ',') {
            field_count++;
            // store length of previous field
            if (field_count > 1) {
                // we need to track lengths properly
            }
            // Actually, let's rethink: we need to count fields and their lengths
            // Let's use a different approach: track current field length
            
            // Reset for next field
        } else {
            // normal character
        }
    }
    
    // Let me rewrite this more carefully
    return 0;
}
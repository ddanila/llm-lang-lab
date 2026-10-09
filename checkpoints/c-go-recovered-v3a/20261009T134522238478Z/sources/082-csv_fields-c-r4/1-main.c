#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Trim trailing LF/CRLF
    while (n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r')) {
        n--;
    }
    
    // If input was empty after trimming, it's one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    size_t fcount = 0;
    size_t flen[5001];
    size_t pos = 0;
    int in_quotes = 0;
    size_t i = 0;
    
    while (i < n) {
        char c = buf[i];
        
        if (c == '"' && !in_quotes) {
            // Check if it's an escaped quote (followed by another quote)
            if (i + 1 < n && buf[i+1] == '"') {
                // Escaped quote, treat as literal part of field
                flen[fcount]++;
                i++;
                continue;
            } else {
                // Start or end of quoted section
                in_quotes = !in_quotes;
            }
        } else if (c == ',' && !in_quotes) {
            // End of field
            fcount++;
            pos = i + 1;
            continue;
        } else {
            flen[fcount]++;
        }
        i++;
    }
    
    // After loop, if we're in quotes, the input is malformed, but spec says valid CSV
    // If not in quotes, we've reached end of last field
    if (!in_quotes) {
        fcount++;
    }
    
    printf("%zu", fcount);
    for (size_t j = 0; j < fcount; j++) {
        printf(" %zu", flen[j]);
    }
    printf("\n");
    
    return 0;
}
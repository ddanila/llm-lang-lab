#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input line by line, handling both LF and CRLF
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (n < sizeof(buf) - 1) {
            buf[n++] = (char)c;
        }
    }
    
    // Handle empty input as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Remove trailing CR if present (CRLF -> LF, then we handle LF above)
    if (n > 0 && buf[n-1] == '\r') {
        n--;
    }
    
    // Remove trailing LF if present
    if (n > 0 && buf[n-1] == '\n') {
        n--;
    }
    
    // Now parse the CSV fields
    int field_count = 0;
    size_t *field_lens = malloc(n + 1);
    char *p = buf;
    char *end = buf + n;
    
    while (p <= end) {
        if (*p == '"') {
            // Quoted field
            field_count++;
            size_t len = 0;
            p++; // skip opening quote
            
            while (p <= end) {
                if (*p == '"') {
                    if (p + 1 <= end && *(p + 1) == '"') {
                        // Escaped quote
                        len++;
                        p += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    len++;
                    p++;
                }
            }
            
            // Skip the closing quote if present
            if (p <= end && *p == '"') {
                p++;
            }
        } else {
            // Unquoted field
            field_count++;
            size_t len = 0;
            while (p <= end && *p != '"' && *p != ',') {
                len++;
                p++;
            }
        }
        
        field_lens[field_count - 1] = len;
    }
    
    // Check if there's trailing comma indicating empty final field
    if (n > 0 && buf[n-1] == ',') {
        // There was a trailing comma, meaning we have an empty final field
        // But our loop already counted it? Let's reconsider.
        // Actually, if input ends with ",", then after processing the comma:
        // - If it was unquoted field ending with comma, that's fine
        // - We need to handle this case
        
        // Re-parse more carefully
    }
    
    // Free and re-implement with proper handling
    free(field_lens);
    
    // Reset
    p = buf;
    end = buf + n;
    field_count = 0;
    
    while (p <= end) {
        if (*p == '"') {
            // Quoted field - count it
            field_count++;
            size_t len = 0;
            p++; // skip opening quote
            
            while (p <= end) {
                if (*p == '"') {
                    if (p + 1 <= end && *(p + 1) == '"') {
                        // Escaped quote
                        len++;
                        p += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    len++;
                    p++;
                }
            }
            
            // Skip the closing quote if present
            if (p <= end && *p == '"') {
                p++;
            }
        } else if (*p == ',') {
            // Empty field between commas or at start
            field_count++;
            p++;
        } else {
            // Unquoted field
            field_count++;
            size_t len = 0;
            while (p <= end && *p != '"' && *p != ',') {
                len++;
                p++;
            }
        }
    }
    
    // Check for empty final field after trailing comma
    if (n > 0 && buf[n-1] == ',') {
        // There's a trailing comma, so there should be one more empty field
        // But wait, let's trace: "a," -> fields: "a" and ""
        // When we see 'a', we count it, then when we see ',', we count empty field
        // So for "a,", p points to 'a', we process unquoted, p moves past 'a'
        // Then p is at ',', which triggers empty field counting
        // Then p moves past ',' and now p > end (or p == end + 1)
        // So loop ends. field_count = 2. Correct.
        
        // But what about just ","? 
        // p starts at first ','. Empty field counted, p moves past ','.
        // Now p > end. Loop ends. field_count = 1. Correct for one empty field.
        
        // What about "," followed by nothing (empty input)?
        // n would be 1 (just the comma), buf[0] = ','
        // p at ',', empty field counted, p moves past ','.
        // Loop ends. field_count = 1. Correct.
    }
    
    // Now print results
    for (int i = 0; i < field_count; i++) {
        if (i > 0) printf(" ");
        printf("%zu", field_lens[i]);
    }
    printf("\n");
    
    return 0;
}
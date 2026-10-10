#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;

    // Read input until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF) {
        if (n < 5000) {
            buf[n++] = (char)c;
        }
    }

    // If input was empty (EOF immediately), treat as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    int field_count = 0;
    
    char *p = buf;
    size_t len = n;

    while (len > 0) {
        if (*p == '"') {
            // Quoted field - skip opening quote
            p++; 
            field_count++;
            
            // Parse until unescaped closing quote or end
            while (p < buf + len) {
                if (*p == '"') {
                    // Check for escaped quote (two consecutive quotes)
                    if (p + 1 < buf + len && *(p + 1) == '"') {
                        // Escaped quote - continue
                        p += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    p++;
                }
            }
            
            // Skip closing quote if present
            if (p < buf + len && *p == '"') {
                p++;
            }
        } else {
            // Unquoted field - parse until comma or end
            while (len > 0 && *p != ',' && *p != '\n' && *p != '\r') {
                p++;
            }
            field_count++;
        }

        // Skip comma if present
        if (len > 0 && *p == ',') {
            p++;
            len--;
        } else {
            // End of fields
            break;
        }
    }

    // Output field count and lengths
    printf("%d", field_count);
    
    char *q = buf;
    size_t f_len;
    
    while (n > 0) {
        if (*q == '"') {
            q++; // skip opening quote
            f_len = 0;
            
            while (q < buf + n) {
                if (*q == '"') {
                    if (q + 1 < buf + n && *(q + 1) == '"') {
                        // Escaped quote - counts as 1 char in decoded field
                        f_len += 1;
                        q += 2;
                    } else {
                        break;
                    }
                } else {
                    f_len++;
                    q++;
                }
            }
            
            if (q < buf + n && *q == '"') {
                q++; // skip closing quote
            }
        } else {
            while (n > 0 && *q != ',' && *q != '\n' && *q != '\r') {
                f_len++;
                q++;
            }
        }
        
        printf(" %zu", f_len);
        
        if (*q == ',') {
            q++;
            n--;
        } else {
            break;
        }
    }
    
    printf("\n");
    
    return 0;
}
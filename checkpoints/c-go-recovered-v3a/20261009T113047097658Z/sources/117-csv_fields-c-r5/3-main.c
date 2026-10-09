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
        }
        buf[n++] = (char)c;
    }
    buf[n] = '\0';
    
    // Handle empty input as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields
    size_t i = 0;
    int first_field = 1;
    
    while (i < n) {
        if (buf[i] == '"') {
            // Quoted field - count only the decoded characters
            size_t len = 0;
            i++; // skip opening quote
            
            while (i < n) {
                if (buf[i] == '"') {
                    if (i + 1 < n && buf[i + 1] == '"') {
                        // Escaped quote - counts as 1 character in decoded field
                        len++;
                        i += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    len++;
                    i++;
                }
            }
            
            if (first_field) {
                printf("%zu", len);
                first_field = 0;
            } else {
                printf(" %zu", len);
            }
            
            // Skip trailing quote if present (shouldn't be for valid CSV)
            if (i < n && buf[i] == '"') {
                i++;
            }
        } else {
            // Unquoted field
            size_t j = i;
            while (i < n && buf[i] != ',' && buf[i] != '\n' && buf[i] != '\r') {
                i++;
            }
            size_t len = i - j;
            
            if (first_field) {
                printf("%zu", len);
                first_field = 0;
            } else {
                printf(" %zu", len);
            }
            
            // Skip comma if present
            if (i < n && buf[i] == ',') {
                i++;
            }
        }
    }
    
    printf("\n");
    return 0;
}
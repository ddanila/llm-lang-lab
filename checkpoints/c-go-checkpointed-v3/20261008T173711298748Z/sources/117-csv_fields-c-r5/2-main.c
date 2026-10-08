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
    
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields - output each field's length separately
    int field_count = 0;
    size_t i = 0;
    
    while (i < n) {
        if (buf[i] == '"') {
            // Quoted field
            field_count++;
            size_t field_len = 0;
            i++; // skip opening quote
            
            while (i < n) {
                if (buf[i] == '"') {
                    if (i + 1 < n && buf[i + 1] == '"') {
                        // Escaped quote - count as one character in decoded field
                        field_len++;
                        i += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    field_len++;
                    i++;
                }
            }
            
            printf("%zu ", field_len);
            
            // Skip any remaining quotes (there shouldn't be any for a valid field)
            while (i < n && buf[i] == '"') {
                i++;
            }
        } else {
            // Unquoted field
            field_count++;
            size_t j = i;
            while (i < n && buf[i] != ',' && buf[i] != '\n' && buf[i] != '\r') {
                i++;
            }
            size_t field_len = i - j;
            printf("%zu ", field_len);
            
            // Skip comma if present
            if (i < n && buf[i] == ',') {
                i++;
            }
        }
    }
    
    // Handle case where we have content but no commas (single field)
    // We already printed the length, so this is fine
    
    printf("\n");
    return 0;
}
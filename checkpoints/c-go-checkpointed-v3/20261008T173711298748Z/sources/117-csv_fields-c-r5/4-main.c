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
    size_t field_count = 0;
    size_t i = 0;
    
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
            
            field_count++;
            
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
            
            field_count++;
            
            // Skip comma if present
            if (i < n && buf[i] == ',') {
                i++;
            }
        }
    }
    
    // Handle case where we have content but no commas (single field)
    // The loop handles this - just one iteration
    
    // Also need to handle trailing empty fields after last comma
    // Check if input ends with comma followed by nothing or newline
    if (n > 0 && buf[n-1] == ',') {
        field_count++;
    }
    
    printf("%zu", field_count);
    
    // Now print each field length - need to re-parse
    i = 0;
    while (i < n) {
        if (buf[i] == '"') {
            size_t len = 0;
            i++; 
            
            while (i < n) {
                if (buf[i] == '"') {
                    if (i + 1 < n && buf[i + 1] == '"') {
                        len++;
                        i += 2;
                    } else {
                        break;
                    }
                } else {
                    len++;
                    i++;
                }
            }
            
            printf(" %zu", len);
            
            if (i < n && buf[i] == '"') {
                i++;
            }
        } else {
            size_t j = i;
            while (i < n && buf[i] != ',' && buf[i] != '\n' && buf[i] != '\r') {
                i++;
            }
            size_t len = i - j;
            
            printf(" %zu", len);
            
            if (i < n && buf[i] == ',') {
                i++;
            }
        }
    }
    
    printf("\n");
    return 0;
}
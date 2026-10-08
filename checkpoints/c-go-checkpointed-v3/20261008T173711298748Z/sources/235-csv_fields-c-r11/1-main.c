#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read input until newline or EOF
    int c;
    while ((c = getchar()) != EOF && c != '\n' && c != '\r') {
        if (n < 5000) {
            buf[n++] = (char)c;
        }
    }
    
    // If no characters read, it's an empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Parse CSV fields
    char *field_start = buf;
    size_t num_fields = 0;
    size_t total_len = 0;
    int in_quotes = 0;
    size_t i = 0;
    
    while (i < n) {
        unsigned char c = (unsigned char)buf[i];
        
        if (in_quotes) {
            if (c == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i + 1] == '"') {
                    i += 2;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    i++;
                }
            } else {
                i++;
            }
        } else {
            if (c == ',') {
                // Field ends here
                num_fields++;
                total_len += (i - field_start);
                field_start = buf + i + 1;
                i++;
            } else if (c == '\n' || c == '\r') {
                // End of record
                num_fields++;
                total_len += (i - field_start);
                break;
            } else {
                i++;
            }
        }
    }
    
    // Handle last field
    if (num_fields == 0) {
        num_fields = 1;
        total_len = n;
    } else {
        // Count the final field
        size_t last_field_len = n - (field_start - buf);
        total_len += last_field_len;
        num_fields++;
    }
    
    printf("%zu", num_fields);
    for (size_t f = 0; f < num_fields; f++) {
        // Calculate length of each field
        size_t pos = 0;
        if (f == 0) {
            pos = 0;
        } else {
            // Find position of f-th comma
            int in_q = 0;
            for (size_t j = 0; j < n && pos < n; j++) {
                unsigned char c = (unsigned char)buf[j];
                if (in_q) {
                    if (c == '"') {
                        if (j + 1 < n && buf[j + 1] == '"') {
                            j++;
                        } else {
                            in_q = 0;
                        }
                    }
                } else {
                    if (c == ',') {
                        pos = j + 1;
                        break;
                    } else if (c != '\n' && c != '\r') {
                        // Continue
                    } else {
                        break;
                    }
                }
            }
        }
        
        size_t field_len = n - pos;
        for (size_t j = 0; j < f && j < num_fields; j++) {
            // Skip to next comma or end
            int in_q = 0;
            for (size_t k = pos; k < n; k++) {
                unsigned char c = (unsigned char)buf[k];
                if (in_q) {
                    if (c == '"') {
                        if (k + 1 < n && buf[k + 1] == '"') {
                            k++;
                        } else {
                            in_q = 0;
                        }
                    }
                } else {
                    if (c == ',') {
                        pos = k + 1;
                        break;
                    } else if (c != '\n' && c != '\r') {
                        // Continue
                    } else {
                        break;
                    }
                }
            }
        }
        
        printf(" %zu", field_len);
    }
    printf("\n");
    
    return 0;
}
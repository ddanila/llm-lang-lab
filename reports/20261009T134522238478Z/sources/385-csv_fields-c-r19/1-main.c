#include <stdio.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n = fread(buf, 1, sizeof(buf), stdin);
    
    // Find the logical end of input (first LF or CRLF, or EOF)
    size_t end = n;
    for (size_t i = 0; i < n - 1; i++) {
        if (buf[i] == '\n') {
            end = i + 1;
            break;
        } else if (buf[i] == '\r' && i + 1 < n && buf[i+1] == '\n') {
            end = i + 2;
            break;
        }
    }
    
    // Handle empty input as one empty field
    if (end == 0) {
        printf("1 0\n");
        return 0;
    }
    
    size_t pos = 0;
    int first = 1;
    while (pos < end) {
        if (first) first = 0; else printf(" ");
        
        // Check for start of quoted field
        if (buf[pos] == '"') {
            // Quoted field
            size_t len = 0;
            pos++; // consume opening quote
            
            while (pos < end) {
                char c = buf[pos];
                if (c == '"') {
                    // Check for escaped quote
                    if (pos + 1 < end && buf[pos+1] == '"') {
                        len += 2; // literal double quote counts as 2 bytes in output
                        pos += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else if (c == '\r' || c == '\n') {
                    // Should not happen per spec, but handle gracefully
                    break;
                } else {
                    len++;
                    pos++;
                }
            }
            
            printf("%zu", len);
        } else {
            // Unquoted field
            size_t start = pos;
            while (pos < end && buf[pos] != ',' && buf[pos] != '\n' && buf[pos] != '\r') {
                pos++;
            }
            printf("%zu", pos - start);
        }
    }
    
    // Handle trailing comma case (last field is empty)
    if (pos < end && buf[pos] == ',') {
        printf(" 0");
    }
    
    printf("\n");
    return 0;
}
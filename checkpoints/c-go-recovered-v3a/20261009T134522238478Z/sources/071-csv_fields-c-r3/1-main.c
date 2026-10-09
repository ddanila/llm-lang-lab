#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned char buf[5001];
    size_t len = 0;
    
    // Read input until EOF or newline
    int c;
    while ((c = getchar()) != EOF && (c != '\n' || len > 0)) {
        if (len < sizeof(buf)) {
            buf[len++] = (unsigned char)c;
        } else {
            // Should not happen given the spec
            break;
        }
    }
    
    // If we hit EOF without any characters, it's an empty input -> 1 field of length 0
    if (len == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // Now parse the CSV record
    int field_count = 0;
    size_t start = 0;
    size_t i = 0;
    
    while (i < len) {
        if (buf[i] == '"') {
            // Quoted field starts
            field_count++;
            size_t j = i + 1;
            
            while (j < len) {
                if (buf[j] == '"') {
                    // Check for escaped quote (two consecutive quotes)
                    if (j + 1 < len && buf[j + 1] == '"') {
                        // Escaped quote, skip both
                        j += 2;
                    } else {
                        // End of quoted field
                        break;
                    }
                } else {
                    j++;
                }
            }
            
            // Now we have the end of the quoted field at position j
            // The next character should be either ',' or '\n' (or EOF)
            // But we need to count bytes in the decoded field
            // For a quoted field, each pair of quotes becomes one quote (1 byte -> 1 byte)
            // Actually, two consecutive quotes become one quote character
            // So we need to count: for each position in original, if it's part of a pair, count 1, else if single, count 0? 
            // No, let's think again.
            // Original: "a""b" -> decoded: a"b (3 bytes)
            // Positions 1,2 are the quotes around the field
            // Position 3 is the first quote of the pair ""
            // Position 4 is the second quote of the pair ""
            // Decoded: position 3 becomes one quote character
            
            // Let's count decoded length for quoted field from i+1 to j-1
            size_t decoded_len = 0;
            size_t k = i + 1;
            while (k < j) {
                if (k + 1 < len && buf[k] == '"' && buf[k + 1] == '"') {
                    // Escaped quote pair, contributes 1 byte to decoded field
                    decoded_len++;
                    k += 2;
                } else {
                    // Regular character (not a quote or not part of escaped pair)
                    decoded_len++;
                    k++;
                }
            }
            
            // Add the quoted field length
            printf("%zu", decoded_len);
            
            // Skip to next field or end
            i = j;
            if (i < len && buf[i] == ',') {
                i++; // skip comma
            } else if (i < len && buf[i] == '\n' || buf[i] == '\r') {
                break;
            }
        } else {
            // Unquoted field
            field_count++;
            size_t j = i;
            
            while (j < len && buf[j] != ',' && buf[j] != '\n' && buf[j] != '\r') {
                j++;
            }
            
            size_t decoded_len = j - i;
            printf("%zu", decoded_len);
            
            i = j;
            if (i < len && buf[i] == ',') {
                i++; // skip comma
            } else if (i < len && buf[i] == '\n' || buf[i] == '\r') {
                break;
            }
        }
    }
    
    printf("\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5000

int main(void) {
    char buf[MAX_LEN];
    size_t n = 0;
    
    // Read input until EOF or newline (but handle CR/LF at end)
    int c;
    while ((c = getchar()) != EOF && n < MAX_LEN - 1) {
        if (c == '\n') break;
        buf[n++] = (char)c;
    }
    
    // Parse CSV fields
    char *p = buf;
    size_t field_count = 0;
    size_t *field_lens = NULL;
    
    while (*p != '\0') {
        if (field_count == 0) {
            // Skip leading spaces - but wait, spaces are significant in CSV?
            // Actually, the spec says "Spaces are significant." but also says unquoted fields contain no quotes or commas.
            // Let me re-read: Fields may be unquoted or enclosed entirely in double quotes.
            // Inside a quoted field, literal double quote is escaped as two consecutive double quotes.
            // Commas and spaces are literal. Unquoted fields contain no quotes or commas.
            // Empty fields, including the final field, are allowed.
            // So spaces between fields (before comma) should be part of unquoted field? 
            // Actually, looking at example: "a,\"b,c\",\n" -> 3 fields with lengths 1, 3, 0
            // Field 1: "a" -> length 1
            // Field 2: "b,c" -> length 3
            // Field 3: empty -> length 0
            // So there's no space handling mentioned. Let me just parse strictly.
        }
        
        // Check if current position is a comma or end of string
        if (*p == ',') {
            field_count++;
            p++;
            continue;
        } else if (*p == '\0') {
            break;
        }
        
        // Determine if field is quoted
        if (*p == '"') {
            // Quoted field - count characters until closing quote (handling escaped quotes)
            char *start = p + 1;
            size_t len = 0;
            while (*p != '\0' && *(p+1) != ',') {
                if (*p == '"') {
                    // Check if it's an escaped quote (two consecutive quotes)
                    if (*(p+1) == '"') {
                        len++; // Count as one character
                        p += 2;
                        continue;
                    } else {
                        break; // End of quoted field
                    }
                } else {
                    len++;
                    p++;
                }
            }
            field_count++;
        } else {
            // Unquoted field - count until comma or end
            char *start = p;
            while (*p != '\0' && *(p+1) != ',') {
                if (*p == '"') {
                    // Quote in unquoted field should be treated as part of the field?
                    // But spec says "Unquoted fields contain no quotes or commas."
                    // So we can assume unquoted fields don't have quotes.
                    // Let's just count all characters until comma.
                }
                p++;
            }
            field_count++;
        }
    }
    
    // Handle the last field if it ends with comma (empty final field)
    if (*p == '\0' && field_count > 0) {
        // Check if we ended at a comma - then there's an empty final field
        // Actually, let me re-think the parsing logic.
    }
    
    // Let me rewrite this more carefully
    
    return 0;
}
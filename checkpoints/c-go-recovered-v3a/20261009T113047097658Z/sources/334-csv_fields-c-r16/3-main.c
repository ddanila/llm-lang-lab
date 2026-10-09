#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 5000

int main(void) {
    char buf[MAX_LEN];
    size_t n = 0;

    // Read input character by character until newline or EOF
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (n < MAX_LEN - 1) {
            buf[n++] = (char)c;
        }
    }
    buf[n] = '\0';

    // Parse fields and count lengths
    size_t num_fields = 0;
    char *fields[MAX_LEN];
    size_t field_lengths[MAX_LEN];

    const char *p = buf;
    
    if (*p == '\0') {
        // Empty input: one empty field
        printf("1 0\n");
        return 0;
    }

    while (1) {
        size_t len = 0;

        if (*p == '"') {
            // Quoted field
            p++; // skip opening quote
            while (*p) {
                if (*p == '"') {
                    if (*(p + 1) == '"') {
                        // Escaped quote, copy both
                        len += 2;
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
            if (*p == '"') {
                p++; // skip closing quote
            }
        } else {
            // Unquoted field
            while (*p && *p != ',' && *p != '\n' && *p != '\0') {
                len++;
                p++;
            }
        }

        if (num_fields < MAX_LEN) {
            fields[num_fields] = NULL;  // placeholder
            field_lengths[num_fields] = len;
            num_fields++;
        }
    }

    // Output results
    printf("%zu", num_fields);
    for (size_t i = 0; i < num_fields; i++) {
        printf(" %zu", field_lengths[i]);
    }
    printf("\n");

    return 0;
}
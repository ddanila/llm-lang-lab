#include <stdio.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    
    // Read up to 5000 bytes, stop at newline or EOF
    int c;
    while ((c = getchar()) != EOF && (n < 5000)) {
        if (c == '\n') break;
        buf[n++] = (char)c;
    }
    
    // Handle empty input case specially
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }
    
    // First pass: count fields and store lengths
    char *p = buf;
    size_t field_count = 0;
    size_t *field_lens = malloc(n + 1);
    if (!field_lens) {
        printf("1 0\n");
        return 0;
    }
    
    while (n > 0 && *p != '\0') {
        if (*p == ',') {
            field_count++;
            field_lens[field_count-1] = 0; // empty field
            p++;
            n--;
            continue;
        }
        
        if (*p == '"') {
            // Quoted field - find closing quote (handling escaped quotes)
            size_t len = 0;
            p++; // skip opening quote
            while (*p != '"') {
                if (*(p+1) == '"') {
                    len++; // count the escaped quote as 1 char
                    p += 2;
                    n -= 2;
                    continue;
                }
                len++;
                p++;
                n--;
            }
            if (*p == '"') {
                p++; // skip closing quote
                n--;
            }
            field_count++;
            field_lens[field_count-1] = len;
        } else {
            // Unquoted field
            size_t len = 0;
            while (*p != ',') {
                p++;
                n--;
                len++;
            }
            if (*p == ',') p++; n--;
            field_count++;
            field_lens[field_count-1] = len;
        }
    }
    
    // Handle remaining content after loop (should be empty or at newline)
    // If we stopped at newline, the last field was already counted
    
    printf("%zu", field_count);
    for (size_t i = 0; i < field_count; i++) {
        printf(" %zu", field_lens[i]);
    }
    printf("\n");
    
    free(field_lens);
    return 0;
}
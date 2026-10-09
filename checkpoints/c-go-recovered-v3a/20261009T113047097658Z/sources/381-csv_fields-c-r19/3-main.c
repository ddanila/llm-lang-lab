#include <stdio.h>
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
    buf[n] = '\0';

    // Handle empty input as one empty field
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    size_t field_count = 0;
    size_t current_len = 0;
    int in_quotes = 0;
    int first_char_is_quote = -1; // -1 unknown, 0 no, 1 yes

    for (size_t i = 0; i < n; i++) {
        if (first_char_is_quote == -1 && buf[i] == '"') {
            first_char_is_quote = 1;
        } else if (buf[i] == '"') {
            // Toggle quote state
            in_quotes = !in_quotes;
            
            if (first_char_is_quote) {
                // Inside a quoted field
                if (in_quotes) {
                    // Just exited quoted section - escaped quote, count one char
                    current_len++;
                } else {
                    // Entered quoted section - skip the closing quote
                    // But wait, we need to handle content between quotes
                }
            } else {
                // Outside quoted field (unquoted), but we shouldn't see quotes here
                // This is an error or malformed input per spec
            }
        } else if (buf[i] == ',') {
            // End of field
            field_lengths[field_count] = current_len;
            field_count++;
            current_len = 0;
            first_char_is_quote = -1; // reset for next field
        } else {
            current_len++;
        }
    }

    // Last field
    field_lengths[field_count] = current_len;
    field_count++;

    // Output
    for (size_t f = 0; f < field_count; f++) {
        if (f > 0) printf(" ");
        printf("%zu", field_lengths[f]);
    }
    printf("\n");

    return 0;
}
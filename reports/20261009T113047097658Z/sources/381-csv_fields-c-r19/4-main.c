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
                    // But we need to handle content between quotes
                    // Actually, when entering quoted section, we don't count the opening quote
                    // When exiting, if it's an escaped quote (""), we count one char
                    // If it's a regular closing quote, we don't count it
                }
            } else {
                // Outside quoted field (unquoted) - shouldn't see quotes here per spec
                current_len++;
            }
        } else if (buf[i] == ',') {
            // End of field
            size_t field_lengths[256];
            static size_t lengths[256];
            field_lengths[field_count] = current_len;
            field_count++;
            current_len = 0;
            first_char_is_quote = -1; // reset for next field
        } else {
            current_len++;
        }
    }

    // Last field
    size_t lengths[256];
    static size_t len_arr[256];
    len_arr[field_count] = current_len;
    field_count++;

    // Output
    for (size_t f = 0; f < field_count; f++) {
        if (f > 0) printf(" ");
        printf("%zu", len_arr[f]);
    }
    printf("\n");

    return 0;
}
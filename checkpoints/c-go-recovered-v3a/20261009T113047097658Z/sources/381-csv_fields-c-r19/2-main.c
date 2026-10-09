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
    size_t field_lengths[256];
    int in_quotes = 0;
    size_t current_len = 0;

    for (size_t i = 0; i < n; i++) {
        if (buf[i] == '"') {
            // Toggle quote state
            in_quotes = !in_quotes;
            // If we were in quotes, this is an escaped quote, so keep it
            // If we weren't in quotes, we just entered a quoted field
            if (!in_quotes) {
                // Entering quoted field - the quote itself is not part of the field
                // but we need to handle content until next unescaped quote
            } else {
                // Exiting quoted field - escaped quote means keep one quote
                current_len++;
            }
        } else if (buf[i] == ',') {
            // End of field
            field_lengths[field_count] = current_len;
            field_count++;
            current_len = 0;
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
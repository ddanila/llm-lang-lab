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

    // Find first quote to determine if unquoted or quoted record
    size_t i = 0;
    int in_quotes = 0;
    size_t field_count = 0;
    size_t field_lengths[256]; // max 5000 fields worst case, but limit is practical

    while (i < n) {
        if (buf[i] == '"') {
            in_quotes = !in_quotes;
            i++;
        } else if (buf[i] == ',') {
            field_count++;
            i++;
        } else {
            i++;
        }
    }

    // Handle trailing quote case (shouldn't happen with valid input, but be safe)
    if (in_quotes && buf[n-1] == '"') {
        // This would be malformed, but per spec input is valid so ignore
    }

    field_count++; // count the last field

    // Now compute lengths of each decoded field
    size_t pos = 0;
    int current_field = 0;
    size_t current_len = 0;
    while (pos < n) {
        if (buf[pos] == '"') {
            // Toggle quote state
            in_quotes = !in_quotes;
            pos++;
        } else if (buf[pos] == ',') {
            // End of field
            field_lengths[current_field] = current_len;
            current_field++;
            current_len = 0;
            pos++;
        } else {
            current_len++;
            pos++;
        }
    }
    field_lengths[current_field] = current_len;

    // Output
    for (size_t f = 0; f < field_count; f++) {
        if (f > 0) printf(" ");
        printf("%zu", field_lengths[f]);
    }
    printf("\n");

    return 0;
}
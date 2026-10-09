#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char buf[5001];
    size_t n = 0;
    int c;

    // Read input until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF) {
        if (n < (size_t)(sizeof(buf) - 1)) {
            buf[n++] = (char)c;
        } else {
            // Buffer full, stop reading
            break;
        }
    }
    buf[n] = '\0';

    // Count fields and compute lengths
    int field_count = 0;
    size_t total_len = 0;
    size_t pos = 0;
    int in_quotes = 0;

    while (pos < n) {
        char ch = buf[pos++];

        if (in_quotes) {
            if (ch == '"') {
                // Check for escaped quote
                if (pos < n && buf[pos] == '"') {
                    // Escaped quote, consume both
                    pos++;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                }
            }
        } else {
            if (ch == ',') {
                // Field ends here
                field_count++;
                total_len += 0; // No length added for delimiter, just count
            } else if (ch == '"') {
                in_quotes = 1;
            }
        }
    }

    // After loop: last field is counted when we hit EOF or newline
    if (field_count == 0) {
        // If no commas, there's exactly one field
        field_count = 1;
    } else {
        // We have at least one comma, so we've seen field_count fields so far
        // The last field is already counted because each comma increments field_count
        // But wait: if input is "a,b", we see 'a', then ',' -> field_count=1, then 'b' -> no more commas
        // So field_count should be incremented after the loop if there's content after last comma
        // Actually, let's rethink:
        // Each time we see a comma, that means a new field starts.
        // The number of fields = number of commas + 1 (for the last field)
        // But we need to count fields properly.

        // Let me restart with a cleaner approach:
    }

    // Reset and do it again cleanly
    field_count = 0;
    size_t current_len = 0;
    in_quotes = 0;

    for (pos = 0; pos < n; pos++) {
        char ch = buf[pos];

        if (in_quotes) {
            if (ch == '"') {
                // Check for escaped quote
                if (pos + 1 < n && buf[pos + 1] == '"') {
                    current_len += 2; // Two quotes become one, but we count decoded length
                    pos++; // Skip the next quote
                } else {
                    in_quotes = 0;
                }
            } else {
                current_len++;
            }
        } else {
            if (ch == ',') {
                field_count++;
                total_len += current_len;
                current_len = 0;
            } else if (ch == '"') {
                in_quotes = 1;
            } else {
                current_len++;
            }
        }
    }

    // Add the last field's length and count it
    total_len += current_len;
    if (current_len > 0 || field_count == 0) {
        field_count++;
    }

    // Now output: number of fields, then each field's decoded length
    printf("%d", field_count);
    for (int i = 0; i < field_count; i++) {
        // We need to recompute lengths since we lost them
        // Let's do it differently: store lengths in an array
    }

    // Better approach: use a fixed-size array for field lengths
    int lengths[128]; // Max fields is 5000, but let's be safe with reasonable limit
    int len_count = 0;
    current_len = 0;
    in_quotes = 0;

    for (pos = 0; pos < n; pos++) {
        char ch = buf[pos];

        if (in_quotes) {
            if (ch == '"') {
                if (pos + 1 < n && buf[pos + 1] == '"') {
                    current_len += 2; // Two quotes in input become one quote in output, but we count the decoded length which is 1
                    pos++;
                } else {
                    in_quotes = 0;
                }
            } else {
                current_len++;
            }
        } else {
            if (ch == ',') {
                lengths[len_count] = current_len;
                len_count++;
                current_len = 0;
            } else if (ch == '"') {
                in_quotes = 1;
            } else {
                current_len++;
            }
        }
    }

    // Last field
    lengths[len_count] = current_len;
    len_count++;

    printf("%d", len_count);
    for (int i = 0; i < len_count; i++) {
        printf(" %d", lengths[i]);
    }
    printf("\n");

    return 0;
}
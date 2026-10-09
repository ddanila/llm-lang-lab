#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[5001];
    size_t n;
    
    // Read input until newline or EOF
    n = 0;
    int done = 0;
    for (int i = 0; i < 5000 && !done; i++) {
        int c = getchar();
        if (c == '\n') {
            done = 1;
        } else if (c == EOF) {
            done = 1;
        } else {
            buf[i] = (char)c;
            n++;
        }
    }
    buf[n] = '\0';
    
    // Parse CSV and count fields, compute lengths
    int field_count = 0;
    size_t field_len[500]; // max possible fields
    
    int in_quotes = 0;
    size_t current_len = 0;
    int i = 0;
    
    while (i < n) {
        char c = buf[i];
        
        if (in_quotes) {
            if (c == '"') {
                // Check for escaped quote
                if (i + 1 < n && buf[i+1] == '"') {
                    // Escaped quote, count as one character
                    current_len++;
                    i++;
                } else {
                    // End of quoted field
                    in_quotes = 0;
                    i++;
                }
            } else {
                current_len++;
                i++;
            }
        } else {
            if (c == '"') {
                // Start of quoted field
                in_quotes = 1;
                current_len++;
                i++;
            } else if (c == ',') {
                // End of unquoted field, store length and count
                field_count++;
                field_len[field_count - 1] = current_len;
                current_len = 0;
                i++;
            } else {
                current_len++;
                i++;
            }
        }
    }
    
    // Handle final field (if input ended with quotes, or if no comma at end)
    // If we are still in_quotes at the end, it means the last field was quoted and closed by newline/EOF
    // The closing quote is already counted, so we need to check if there's a closing quote
    // Actually, our logic handles it: when we see a single quote while in_quotes, we exit quotes
    // But we need to handle the case where the file ends without a trailing comma
    
    // If we are still inside quotes at EOF (no closing quote), that would be invalid input
    // Per spec, input is valid, so if we end with unclosed quotes, it's invalid - but problem says valid input
    // So we should have closed all quotes by now unless the last field was empty and quoted?
    
    // Let's reconsider: after processing, if in_quotes is still 1, then we need to check if there's a closing quote
    // Actually, our loop processes character by character. When we see a single " while in_quotes, we exit.
    // So at EOF, in_quotes should be 0 for valid input.
    
    // But wait - what if the last field is quoted and closed? Then we would have exited quotes
    // and current_len would be the length of that field (without the closing quote).
    
    // Actually there's an issue: when we exit quotes, we don't store the field yet.
    // We need to handle the final field after the loop.
    
    if (in_quotes) {
        // This shouldn't happen for valid input, but let's handle it gracefully
        // It means we have an unclosed quoted field - but spec says valid input
        // For now, just count what we have
    } else {
        // Store the last field
        field_count++;
        field_len[field_count - 1] = current_len;
    }
    
    // Also handle empty input case - if n == 0, we should output "1 0"
    // Our logic: if buf is empty (n==0), the loop doesn't run, in_quotes=0, current_len=0
    // Then after loop, field_count=0, then we add one more field with length 0 -> field_count=1, correct!
    
    // But wait - what about input like "\"a\"" without newline? That's valid too.
    // Our code should handle that. Let me trace:
    // buf = "\"a\"", n=4 (including closing quote)
    // i=0: c='"', in_quotes=1, current_len=1, i=1
    // i=1: c='a', current_len=2, i=2
    // i=2: c='"', exit quotes, in_quotes=0, i=3
    // i=3: loop ends (i < n is false)
    // After loop: in_quotes=0, so field_count++, field_len[0]=current_len=2
    // But the actual decoded field is "a" which is 1 byte, not 2!
    
    // Ah, I see the issue. When we exit quotes, we don't remove the closing quote from current_len.
    // We need to adjust current_len when exiting quotes.
    
    // Let me fix this by decrementing current_len when we exit a quoted field
    // But actually, let's think differently: the decoded field length should not include the quotes.
    // So when we enter quotes, we don't count the opening quote.
    // When we see a closing quote (single), we don't count it either.
    
    // Revised approach: track whether we're in a quoted field, and only count content between quotes
    // For escaped quotes ("\""), count as 1 character
    
    // Let me rewrite the logic more carefully
}
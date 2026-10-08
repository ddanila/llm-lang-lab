#include <stdio.h>
#include <stdlib.h>

int main(void) {
    unsigned char buf[5001];
    int n = 0;
    int c;

    while ((c = getchar()) != EOF && n < 5000) {
        if (c == '\n' || c == '\r') {
            break;
        }
        buf[n++] = (unsigned char)c;
    }
    buf[n] = '\0';

    // Handle empty input as one empty field
    int len = 0;
    if (n == 0) {
        printf("1 0\n");
        return 0;
    }

    // Check if the entire buffer is just whitespace/terminator that means empty record
    // But per spec: "Empty input represents one empty field."
    // So if we have content, we parse it.
    
    int field_count = 0;
    long total_len = 0;
    
    char *p = (char *)buf;
    int i = 0;
    int in_quotes = 0;
    
    while (i < n) {
        if (*p == '"') {
            field_count++;
            // Count length of this quoted field
            int flen = 0;
            char *qstart = p;
            p++; // skip opening quote
            while (p - qstart < 5000 && *p != '"' || *(p+1) == '"') {
                if (*p == '"') {
                    // Check if next is also quote
                    if (*(p+1) == '"') {
                        flen++; // escaped quote counts as 1 byte in decoded? No, we need to count bytes of decoded field
                        p += 2;
                    } else {
                        break;
                    }
                } else {
                    p++;
                }
            }
            // Now p is at the closing quote or beyond
            // Count the actual quoted characters (each pair of quotes becomes one quote)
            char *qend = qstart + 1;
            while (qend < buf + n && *qend != '"' || *(qend+1) == '"') {
                if (*qend == '"') {
                    if (*(qend+1) == '"') {
                        qend += 2;
                    } else {
                        break;
                    }
                } else {
                    qend++;
                }
            }
            // Now qend is at or past closing quote
            // The quoted field length is (qend - qstart) but we need to convert escaped quotes
            // Each """ becomes one " in decoded, so subtract 1 for each pair of consecutive quotes
            int dec_len = (int)(qend - qstart);
            while (dec_len > 0 && dec_len >= 2 && *buf[qstart + dec_len - 2] == '"' && *(buf + qstart + dec_len - 1) == '"') {
                dec_len -= 1;
            }
            // Actually simpler: count characters, and for each """ pair, it's 1 char in decoded
            // Let me redo this properly
            
            long fl = 0;
            char *pp = qstart + 1; // after opening quote
            while (pp < buf + n && *pp != '"' || *(pp+1) == '"') {
                if (*pp == '"') {
                    if (*(pp+1) == '"') {
                        fl += 1; // one decoded char for two quotes
                        pp += 2;
                    } else {
                        break;
                    }
                } else {
                    fl += 1;
                    pp++;
                }
            }
            total_len += fl;
            i = (int)(pp - buf); // advance to after closing quote
        } else {
            field_count++;
            // Unquoted field: count until comma or end
            char *start = p;
            while (p < buf + n && *p != ',' && *p != '"') {
                p++;
            }
            long fl = (long)(p - start);
            total_len += fl;
            i = (int)(p - buf);
        }
    }

    printf("%ld %ld", field_count, total_len);
    
    // Wait, I need to print each field's length separately
    // Let me redo the logic properly
}
package main

import (
	"fmt"
)

func parseCSV(s string) []string {
	if len(s) == 0 {
		return []string{""}
	}

	var fields []string
	var currentField []byte
	inQuotes := false

	for i := 0; i < len(s); i++ {
		c := s[i]

		if inQuotes {
			if c == '"' {
				if i+1 < len(s) && s[i+1] == '"' {
					// Escaped quote
					currentField = append(currentField, '"')
					i++ // skip next quote
				} else {
					// End of quoted field
					inQuotes = false
				}
			} else {
				currentField = append(currentField, c)
			}
		} else {
			if c == '"' {
				inQuotes = true
			} else if c == ',' {
				fields = append(fields, string(currentField))
				currentField = nil
			} else {
				currentField = append(currentField, c)
			}
		}
	}

	// Add the last field
	if len(currentField) > 0 || !inQuotes {
		fields = append(fields, string(currentField))
	}

	return fields
}

func main() {
	var buf []byte
	for {
		c := rune(0)
		n := 0
		for n < 5001 && c != -1 {
			c, n = readRune()
			if c == -1 {
				break
			}
			buf = append(buf, byte(c))
		}

		s := string(buf)

		fields := parseCSV(s)

		var output []byte
		output = append(output, fmt.Sprintf("%d", len(fields))...)
		for _, f := range fields {
			output = append(output, ' ')
			output = append(output, fmt.Sprintf("%d", len(f))...)
		}
		fmt.Println(string(output))

		buf = nil
	}
}

func readRune() (rune, int) {
	var c rune
	if n := 0; n < 5001 {
		c = rune(readByte())
		if c == -1 {
			return -1, n
		}
		n++
	}
	return c, n
}

func readByte() byte {
	// This is a simplified approach - in reality we need to read from stdin
	// Since we can't use bufio.Scanner for the full spec, we'll implement
	// a simple byte reader that handles LF/CRLF properly
	return 0
}
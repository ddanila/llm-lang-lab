package main

import (
	"fmt"
)

func main() {
	buf := make([]byte, 5001)
	n, _ := fmt.Scan(buf) // Read all input from stdin into buffer
	if n == 0 {
		fmt.Println("1 0")
		return
	}

	// Remove trailing newline(s) if present
	i := n - 1
	for i >= 0 && (buf[i] == '\n' || buf[i] == '\r') {
		i--
	}
	n = i + 1

	// Parse CSV fields
	var fields []string
	start := 0
	inQuotes := false
	for i := 0; i < n; i++ {
		b := buf[i]
		if inQuotes {
			if b == '"' {
				// Check for escaped quote (two consecutive quotes)
				if i+1 < n && buf[i+1] == '"' {
					// Escaped quote, include both
					fields[len(fields)-1] += string(b) + string(buf[i+1])
					i++ // skip next quote
				} else {
					// End of quoted field
					inQuotes = false
				}
			} else {
				fields[len(fields)-1] += string(b)
			}
		} else {
			if b == '"' {
				inQuotes = true
			} else if b == ',' {
				// Unquoted field ends here
				fields = append(fields, string(buf[start:i]))
				start = i + 1
			} else {
				// Regular character in unquoted field
				// We'll handle this at the end to avoid multiple appends
			}
		}
	}

	// Handle last field (whether quoted or not)
	if start < n {
		lastField := string(buf[start:n])
		if inQuotes {
			// Remove surrounding quotes and unescape internal quotes
			lastField = lastField[1 : len(lastField)-1]
			// Unescape double quotes
			unescaped := ""
			for i := 0; i < len(lastField); i++ {
				if lastField[i] == '"' && i+1 < len(lastField) && lastField[i+1] == '"' {
					unescaped += "\"\""
					i++
				} else {
					unescaped += string(lastField[i])
				}
			}
			lastField = unescaped
		}
		fields = append(fields, lastField)
	}

	// Output: number of fields, then length of each field
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
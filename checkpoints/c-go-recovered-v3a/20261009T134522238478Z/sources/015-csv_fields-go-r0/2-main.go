package main

import (
	"bufio"
	"fmt"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	buf, err := reader.ReadBytes('\n')
	if err != nil && err.Error() == "EOF" {
		fmt.Println("1 0")
		return
	}
	
	// Handle empty input (no bytes read)
	if len(buf) == 0 {
		fmt.Println("1 0")
		return
	}
	
	// Remove trailing newline(s) if present
	n := len(buf)
	for n > 0 && (buf[n-1] == '\n' || buf[n-1] == '\r') {
		n--
	}
	
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
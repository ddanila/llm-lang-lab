package main

import (
	"bufio"
	"fmt"
	"os"
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
	
	// Parse CSV fields using a proper state machine
	var field string
	var fields []string
	inQuotes := false
	
	for i := 0; i < n; i++ {
		b := buf[i]
		if inQuotes {
			if b == '"' {
				// Check for escaped quote (two consecutive quotes)
				if i+1 < n && buf[i+1] == '"' {
					field += "\"\""  // Escaped quote becomes single literal quote
					i++ // skip next quote
				} else {
					// End of quoted field
					inQuotes = false
				}
			} else {
				field += string(b)
			}
		} else {
			if b == '"' {
				inQuotes = true
				field = ""  // Start new quoted field
			} else if b == ',' {
				// Unquoted field ends here
				fields = append(fields, field)
				field = ""
			} else {
				// Regular character in unquoted field
				field += string(b)
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
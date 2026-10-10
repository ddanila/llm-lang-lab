package main

import (
	"bytes"
	"fmt"
)

func parseCSV(s []byte) ([]string, error) {
	var fields []string
	
	i := 0
	start := 0
	
	for i < len(s) {
		if s[i] == '"' {
			// Start of quoted field
			i++ // skip opening quote
			fieldStart := i
			
			for i < len(s) {
				if s[i] == '"' {
					// Check for escaped quote (two consecutive quotes)
					if i+1 < len(s) && s[i+1] == '"' {
						i += 2 // skip both quotes
					} else {
						// End of quoted field
						i++ // skip closing quote
						fields = append(fields, string(s[fieldStart:i-1]))
						break
					}
				} else {
					i++
				}
			}
		} else if s[i] == ',' {
			// Unquoted field ends here
			field := string(s[start:i])
			fields = append(fields, field)
			start = i + 1
		} else {
			i++
		}
	}
	
	// Last field (if any remaining)
	if start < len(s) {
		field := string(s[start:len(s)])
		fields = append(fields, field)
	}
	
	return fields, nil
}

func main() {
	var buf bytes.Buffer
	
	// Read from stdin - read up to 5001 bytes or EOF
	data := make([]byte, 5001)
	n, _ := buf.Read(data) // n is not used
	
	input := buf.Bytes()
	
	// Handle empty input as one empty field
	if len(input) == 0 {
		fmt.Println("1 0")
		return
	}
	
	fields, err := parseCSV(input)
	if err != nil {
		fmt.Println("Error parsing CSV:", err)
		return
	}
	
	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
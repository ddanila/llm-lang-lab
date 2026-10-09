package main

import (
	"bytes"
	"fmt"
)

func parseCSV(s []byte) ([]string, error) {
	var fields []string
	start := 0
	i := 0
	
	for i < len(s) {
		if s[i] == '"' {
			// Quoted field
			i++ // skip opening quote
			fieldStart := i
			for i < len(s) {
				if s[i] == '"' {
					if i+1 < len(s) && s[i+1] == '"' {
						// escaped quote
						i += 2
					} else {
						// end of quoted field
						i++ // skip closing quote
						fields = append(fields, string(s[fieldStart:i-1]))
						break
					}
				} else {
					i++
				}
			}
			if i >= len(s) && s[i-1] == '"' {
				// Unterminated quoted field - treat as error or handle gracefully
				// For this problem, we assume valid input
				return nil, fmt.Errorf("unterminated quoted field")
			}
		} else if s[i] == ',' {
			// Unquoted field
			field := string(s[start:i])
			fields = append(fields, field)
			start = i + 1
		} else {
			i++
		}
	}
	
	// Last field
	if start < len(s) {
		field := string(s[start:len(s)])
		fields = append(fields, field)
	}
	
	return fields, nil
}

func main() {
	var buf bytes.Buffer
	
	// Read from stdin
	data := make([]byte, 5001)
	buf.Read(data) // n is not used, just read up to buffer limit
	
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
package main

import (
	"bufio"
	"fmt"
)

func main() {
	reader := bufio.NewReaderSize(nil, 5001)
	
	// Read input from stdin until EOF or newline
	buf := make([]byte, 0, 5000)
	var n int
	for {
		b, err := reader.ReadByte()
		if err != nil {
			break
		}
		buf = append(buf, b)
		n++
	}
	
	// If input is empty (n == 0), treat as one empty field
	if n == 0 {
		fmt.Println("1 0")
		return
	}
	
	// Parse CSV fields
	fields := parseCSV(string(buf))
	
	// Output number of fields and their lengths
	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSV(input string) []string {
	var fields []string
	start := 0
	
	i := 0
	n := len(input)
	
	for i < n {
		if input[i] == '"' {
			// Quoted field
			start = i + 1
			i++
			
			fieldBytes := make([]byte, 0, n-start)
			
			for i < n {
				if input[i] == '"' {
					// Check if this is an escaped quote or end of field
					if i+1 < n && input[i+1] == '"' {
						// Escaped quote: include both quotes in the decoded value
						fieldBytes = append(fieldBytes, '"')
						i += 2
					} else {
						// End of quoted field
						i++ // skip closing quote
						break
					}
				} else {
					fieldBytes = append(fieldBytes, input[i])
					i++
				}
			}
			
			fields = append(fields, string(fieldBytes))
		} else if input[i] == ',' {
			// Unquoted field ends at comma
			field := input[start:i]
			fields = append(fields, field)
			start = i + 1
			i++
		} else {
			i++
		}
	}
	
	// Add the last field if there is any content after the last comma or quote
	if start < len(input) {
		field := input[start:]
		fields = append(fields, field)
	}
	
	return fields
}
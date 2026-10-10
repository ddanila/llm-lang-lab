package main

import (
	"fmt"
)

func main() {
	buf := make([]byte, 5001)
	n, err := fmt.Scanln(buf)
	if n < 0 {
		fmt.Println("1 0")
		return
	}
	
	data := buf[:n]
	
	// Handle empty input (no bytes read)
	if len(data) == 0 {
		fmt.Println("1 0")
		return
	}
	
	fields := parseCSV(data)
	
	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	start := 0
	
	i := 0
	for i < len(data) && data[i] != '\n' && data[i] != '\r' {
		if data[i] == '"' {
			// Quoted field starts
			i++ // skip opening quote
			fieldStart := i
			
			// Read until closing quote or end
			for i < len(data) && data[i] != '"' {
				i++
			}
			
			if i < len(data) && data[i] == '"' {
				// Skip closing quote
				i++
				
				// Decode escaped quotes (each pair of "" becomes one ")
				decoded := make([]byte, 0, (i-fieldStart)/2)
				for j := fieldStart; j < i; j += 2 {
					decoded = append(decoded, '"')
				}
				fields = append(fields, decoded)
			} else {
				// Unterminated quoted field - take rest of data
				fields = append(fields, data[fieldStart:])
			}
			
			start = i
		} else if data[i] == ',' {
			// Unquoted field
			if start < i {
				fields = append(fields, data[start:i])
			}
			start = i + 1
		} else {
			// Regular character in unquoted field
			continue
		}
		i++
	}
	
	// Add last field if any content remains
	if start < len(data) || fields == nil {
		end := len(data)
		if end > start && data[end-1] == '"' {
			end--
		}
		fields = append(fields, data[start:end])
	} else if len(fields) == 0 {
		// Empty input case - single empty field
		fields = [][]byte{[]byte("")}
	}
	
	return fields
}
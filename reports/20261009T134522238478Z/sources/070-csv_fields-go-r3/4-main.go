package main

import (
	"fmt"
)

func main() {
	buf := make([]byte, 5001)
	n, _ := fmt.Scanln(buf)
	
	if n <= 0 {
		fmt.Println("1 0")
		return
	}
	
	data := buf[:n]
	
	fields := parseCSV(data)
	
	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	
	i := 0
	for i < len(data) {
		if data[i] == '"' {
			// Start of quoted field - skip opening quote
			i++
			
			fieldStart := i
			
			// Read until closing quote or end
			for i < len(data) && data[i] != '"' {
				i++
			}
			
			if i < len(data) && data[i] == '"' {
				// Skip closing quote
				i++
				
				// Decode escaped quotes: each pair of "" becomes one "
				decoded := make([]byte, 0, (i-fieldStart)/2)
				for j := fieldStart; j < i; j += 2 {
					decoded = append(decoded, '"')
				}
				fields = append(fields, decoded)
			} else {
				// Unterminated quoted field - take rest as content
				fields = append(fields, data[fieldStart:])
			}
			
		} else if data[i] == ',' {
			// End of unquoted field
			if i > 0 || len(fields) == 0 {
				fields = append(fields, nil) // empty field
			}
			i++
		} else {
			// Regular character in unquoted field
			if len(fields) == 0 || fields[len(fields)-1] == nil {
				fields = append(fields, make([]byte, 0, len(data)-i))
			}
			fields[len(fields)-1] = append(fields[len(fields)-1], data[i])
			i++
		}
	}
	
	return fields
}
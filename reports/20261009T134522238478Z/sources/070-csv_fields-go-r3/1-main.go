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
	if len(data) == 0 {
		return [][]byte{[]byte("")}
	}
	
	var fields [][]byte
	start := 0
	
	for i := 0; i < len(data); i++ {
		b := data[i]
		
		if b == '"' {
			// Quoted field
			if start < i {
				fields = append(fields, data[start:i])
				start = i + 1
			}
			
			// Skip the opening quote
			i++
			
			// Parse quoted content
			fieldStart := i
			for i < len(data) && data[i] != '"' {
				i++
			}
			
			if i < len(data) && data[i] == '"' {
				// Find end of quoted field
				end := i + 1
				for end < len(data) && data[end] != '"' {
					end++
				}
				// Skip closing quote
				if end < len(data) && data[end] == '"' {
					end++
				}
				
				// Decode escaped quotes
				decoded := make([]byte, 0, (end-fieldStart)/2)
				for j := fieldStart; j < end; j += 2 {
					decoded = append(decoded, '"')
				}
				fields = append(fields, decoded)
				
				start = end
			} else {
				// Unterminated quote - treat rest as content
				fields = append(fields, data[fieldStart:])
				start = i + 1
			}
		} else if b == ',' {
			// Unquoted field ends here
			if start < i {
				fields = append(fields, data[start:i])
				start = i + 1
			}
		}
	}
	
	// Add last field (or empty if no trailing comma)
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
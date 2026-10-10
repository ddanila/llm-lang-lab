package main

import (
	"bufio"
	"fmt"
)

func main() {
	reader := bufio.NewReaderSize(nil, 5001) // Use nil to read from stdin
	buf := make([]byte, 0, 5000)
	
	for {
		b, err := reader.ReadByte()
		if err != nil {
			break
		}
		buf = append(buf, b)
		
		// Check if we've reached end of input (EOF signaled by ReadByte error)
		// But since we're in a loop, we need to check after each read
		_ = err // suppress unused variable warning
		
		// Actually, let's restructure: read until EOF
	}
	
	// Let me rewrite this more carefully
	buf = buf[:0]
	for {
		b, err := reader.ReadByte()
		if err != nil {
			break
		}
		buf = append(buf, b)
	}
	
	result := parseCSV(buf)
	fmt.Println(result[0], result[1:]...)
}

func parseCSV(data []byte) []int {
	var fields []string
	i := 0
	
	for i < len(data) {
		if data[i] == '"' {
			// Quoted field
			start := i + 1
			i++
			for i < len(data) {
				if data[i] == '"' {
					// Check for escaped quote
					if i+1 < len(data) && data[i+1] == '"' {
						// Escaped quote, add literal quote to field
						fields = append(fields, string(data[start:i]))
						i += 2
					} else {
						// End of quoted field
						break
					}
				} else {
					fields = append(fields, string(data[start:i]))
					i++
				}
			}
			// Skip comma or end of record
			if i < len(data) && data[i] == ',' {
				i++
			}
		} else if data[i] == ',' {
			fields = append(fields, "")
			i++
		} else {
			// Regular character in unquoted field
			start := i
			for i < len(data) && data[i] != ',' {
				i++
			}
			fields = append(fields, string(data[start:i]))
		}
	}
	
	// Calculate lengths
	result := make([]int, len(fields)+1)
	result[0] = len(fields)
	for j, f := range fields {
		result[j+1] = len(f)
	}
	return result
}
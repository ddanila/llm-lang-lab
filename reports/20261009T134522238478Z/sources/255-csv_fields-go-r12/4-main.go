package main

import (
	"bytes"
	"fmt"
	"os"
)

func main() {
	data := make([]byte, 0, 5000)
	
	r := os.Stdin
	buf := make([]byte, 1)
	for {
		n, err := r.Read(buf)
		if n > 0 {
			data = append(data, buf[0])
		} else if err != nil {
			break
		}
	}
	
	result := parseCSV(data)
	fmt.Println(result[0])
	for _, l := range result[1:] {
		fmt.Print(" ", l)
	}
	fmt.Println()
}

func parseCSV(data []byte) []int {
	var fields []string
	i := 0
	
	for i < len(data) {
		if data[i] == '"' {
			// Quoted field
			start := i + 1
			i++
			fieldStart := start
			for i < len(data) {
				if data[i] == '"' {
					// Check for escaped quote
					if i+1 < len(data) && data[i+1] == '"' {
						// Escaped quote, continue
						i += 2
					} else {
						// End of quoted field
						break
					}
				} else {
					i++
				}
			}
			fields = append(fields, string(data[fieldStart:i]))
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
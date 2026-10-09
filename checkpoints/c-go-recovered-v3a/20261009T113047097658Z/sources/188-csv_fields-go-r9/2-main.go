package main

import (
	"fmt"
)

func main() {
	var buf [5000]byte
	n := 0
	for {
		c, err := fmt.Scan(&buf[n])
		if err != nil || c == 0 {
			break
		}
		buf[n] = byte(c)
		n++
	}

	fields := parseCSV(buf[:n])
	
	fmt.Print(len(fields))
	for i, f := range fields {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(len(f))
	}
	fmt.Println()
}

func parseCSV(b []byte) [][]byte {
	if len(b) == 0 {
		return [][]byte{nil}
	}

	var fields [][]byte
	start := 0
	i := 0
	
	for i < len(b) {
		c := b[i]
		
		if c == '"' {
			// Quoted field - find the end
			fieldStart := start
			i++ // skip opening quote
			
			for i < len(b) {
				if b[i] == '"' {
					if i+1 < len(b) && b[i+1] == '"' {
						// Escaped quote - consume both
						i += 2
					} else {
						// End of quoted field
						break
					}
				} else {
					i++
				}
			}
			
			// Field is from fieldStart to i (exclusive)
			fields = append(fields, b[fieldStart:i])
			start = i + 1 // move past the closing quote
		} else {
			// Unquoted field - consume until comma or space
			for i < len(b) && b[i] != ',' && b[i] != ' ' {
				i++
			}
		}
		
		// Skip commas and spaces after a field
		for i < len(b) && b[i] == ',' {
			i++
		}
		for i < len(b) && b[i] == ' ' {
			i++
		}
	}
	
	// Check if there's content left (last field)
	if start < len(b) {
		fields = append(fields, b[start:])
	}
	
	return fields
}
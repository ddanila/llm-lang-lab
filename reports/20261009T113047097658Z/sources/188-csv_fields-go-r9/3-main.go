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
	
	for start < len(b) {
		c := b[start]
		
		if c == '"' {
			// Quoted field
			start++ // skip opening quote
			fieldEnd := start
			
			for fieldEnd < len(b) {
				if b[fieldEnd] == '"' {
					if fieldEnd+1 < len(b) && b[fieldEnd+1] == '"' {
						// Escaped quote - include both and move past them
						fieldEnd += 2
					} else {
						// End of quoted field
						break
					}
				} else {
					fieldEnd++
				}
			}
			
			// Field is from the original start to fieldEnd (exclusive)
			fields = append(fields, b[start:fieldEnd])
			start = fieldEnd + 1 // move past closing quote
			
			// Skip comma and spaces after quoted field
			for start < len(b) && b[start] == ',' {
				start++
			}
			for start < len(b) && b[start] == ' ' {
				start++
			}
		} else if c == ',' {
			// Empty unquoted field followed by comma
			fields = append(fields, nil)
			start++
		} else {
			// Unquoted field - consume until comma or space
			fieldEnd := start
			for fieldEnd < len(b) && b[fieldEnd] != ',' && b[fieldEnd] != ' ' {
				fieldEnd++
			}
			fields = append(fields, b[start:fieldEnd])
			start = fieldEnd
			
			// Skip comma and spaces after unquoted field
			for start < len(b) && b[start] == ',' {
				start++
			}
			for start < len(b) && b[start] == ' ' {
				start++
			}
		}
	}
	
	return fields
}
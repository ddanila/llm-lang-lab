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

	// Parse CSV fields from buf[0:n]
	fields := parseCSV(buf[:n])
	
	// Print number of fields
	fmt.Print(len(fields))
	
	// Print length of each field
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
			// Quoted field
			fieldStart := start
			i++ // skip opening quote
			end := -1
			
			for i < len(b) {
				if b[i] == '"' {
					if i+1 < len(b) && b[i+1] == '"' {
						// Escaped quote
						i += 2
					} else {
						// End of quoted field
						end = i
						break
					}
				} else {
					i++
				}
			}
			
			if end == -1 {
				// No closing quote found, treat as literal from start to end
				fields = append(fields, b[fieldStart:])
				return fields
			}
			
			// Include the closing quote in the field (it's part of the quoted content)
			// Actually, we need to include everything up to and including the closing quote
			// But wait - the spec says "enclosed entirely in double quotes"
			// So the field is from start to end+1 (exclusive), not including the quotes themselves
			// Let me re-read... "Inside a quoted field, a literal double quote is escaped as two consecutive double quotes"
			// This suggests we need to unescape the quotes
			fields = append(fields, b[fieldStart:end]) // from start to end (exclusive of end)
			start = i + 1 // move past the closing quote and any following comma
		} else {
			// Unquoted field
			i++
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
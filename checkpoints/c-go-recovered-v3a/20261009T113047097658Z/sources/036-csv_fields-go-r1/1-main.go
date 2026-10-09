package main

import (
	"bufio"
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	r := bufio.NewReaderSize(nil, 5001)
	
	// Read input byte by byte until EOF or newline
	for {
		b, err := r.ReadByte()
		if err != nil {
			break
		}
		buf[n] = b
		n++
		
		if b == '\n' || b == '\r' {
			// Skip CRLF if present
			if b == '\r' {
				r.Peek(1) // Check for LF after CR
			}
			break
		}
	}
	
	input := string(buf[:n])
	
	// Parse CSV fields
	fields := parseCSV(input)
	
	// Output: number of fields, then length of each field
	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSV(s string) []string {
	if s == "" {
		return []string{""}
	}
	
	fields := make([]string, 0)
	var field []byte
	inQuotes := false
	
	for i := 0; i < len(s); i++ {
		b := s[i]
		
		if inQuotes {
			if b == '"' {
				// Check if it's an escaped quote (two consecutive quotes)
				if i+1 < len(s) && s[i+1] == '"' {
					field = append(field, '"')
					i++ // Skip next quote
				} else {
					inQuotes = false
				}
			} else {
				field = append(field, b)
			}
		} else {
			if b == '"' {
				inQuotes = true
			} else if b == ',' {
				fields = append(fields, string(field))
				field = nil
			} else {
				field = append(field, b)
			}
		}
	}
	
	// Add the last field
	if len(field) > 0 || (len(s) > 0 && !inQuotes) {
		fields = append(fields, string(field))
	}
	
	return fields
}
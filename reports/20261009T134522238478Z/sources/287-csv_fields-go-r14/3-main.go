package main

import (
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	
	r := make([]byte, 4096)
	n := 0
	
	for n > 0 {
		n = len(r)
		_, err := buf.Read(r)
		if err != nil {
			break
		}
	}
	
	bufLen := len(buf.Bytes())
	if bufLen == 0 {
		fmt.Println("1 0")
		return
	}
	
	data := buf.Bytes()
	
	// Remove trailing \n or \r\n if present
	l := len(data)
	for l > 0 && (data[l-1] == '\n' || data[l-1] == '\r') {
		l--
	}
	data = data[:l]
	
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
	start := 0
	inQuoted := false
	
	for i < len(data) {
		ch := data[i]
		
		if inQuoted {
			if ch == '"' {
				// Check if this is an escaped quote (next char is also quote)
				if i+1 < len(data) && data[i+1] == '"' {
					i++ // Skip the next quote, continue in field
				} else {
					// End of quoted field
					inQuoted = false
					start = i + 1
				}
			} else if ch == ',' {
				// Comma inside quoted field is literal part of the field
				i++
			} else {
				i++
			}
		} else {
			if ch == '"' {
				inQuoted = true
				start = i + 1
			} else if ch == ',' {
				// Unquoted field ends
				field := make([]byte, i-start)
				copy(field, data[start:i])
				fields = append(fields, field)
				start = i + 1
			} else {
				i++
			}
		}
	}
	
	// Add the last field if any remaining data
	if len(data) > start {
		field := make([]byte, len(data)-start)
		copy(field, data[start:])
		fields = append(fields, field)
	}
	
	return fields
}
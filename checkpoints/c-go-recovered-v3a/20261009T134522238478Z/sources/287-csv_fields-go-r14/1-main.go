package main

import (
	"bufio"
	"fmt"
)

func main() {
	reader := bufio.NewReaderSize(nil, 5001)
	
	var buf []byte
	
	for {
		ch, err := reader.ReadByte()
		if err != nil {
			break
		}
		buf = append(buf, ch)
		
		if len(buf) == 1 {
			continue
		}
		
		if ch == '\n' || ch == '\r' {
			break
		}
	}
	
	// Remove trailing \n or \r\n if present
	l := len(buf)
	for l > 0 && (buf[l-1] == '\n' || buf[l-1] == '\r') {
		l--
	}
	buf = buf[:l]
	
	if len(buf) == 0 {
		fmt.Println("1 0")
		return
	}
	
	fields := parseCSV(buf)
	
	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	start := 0
	
	for i := 0; i < len(data); i++ {
		ch := data[i]
		
		if ch == '"' {
			// Check if it's an escaped quote (part of quoted field)
			if i+1 < len(data) && data[i+1] == '"' {
				i++ // Skip the next quote
			} else {
				// End of quoted field or start of unquoted field
				// Find the end of the field
				end := i + 1
				for end < len(data) && data[end] != ',' {
					end++
				}
				
				if end > start {
					field := make([]byte, end-start)
					copy(field, data[start:end])
					fields = append(fields, field)
				}
				start = end + 1 // Skip the comma
			}
		} else if ch == ',' {
			if i > start {
				field := make([]byte, i-start)
				copy(field, data[start:i])
				fields = append(fields, field)
			}
			start = i + 1
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
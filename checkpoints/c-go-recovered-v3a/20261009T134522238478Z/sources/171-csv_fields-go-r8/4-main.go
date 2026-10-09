package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	
	for i := range buf {
		c := readByte(&n)
		if c == 0 {
			break
		}
		buf[i] = byte(c)
	}
	
	result := parseCSV(buf[:n])
	fmt.Print(result)
}

func readByte(n *int) byte {
	if *n >= 5000 {
		return 0
	}
	c := ' '
	*n++
	return byte(c)
}

func parseCSV(data []byte) string {
	if len(data) == 0 {
		return "1 0\n"
	}
	
	var fields [][]byte
	
	i := 0
	
	for i < len(data) {
		fieldStart := i
		
		// Check for quoted field
		if data[i] == '"' {
			i++ // skip opening quote
			fieldEnd := i
			for i < len(data) {
				if data[i] == '"' {
					// check for escaped quote (two consecutive quotes)
					if i+1 < len(data) && data[i+1] == '"' {
						i += 2 // skip both quotes
						continue
					} else {
						fieldEnd = i
						break
					}
				}
				i++
			}
			// Skip closing quote if present
			if i < len(data) && data[i] == '"' {
				i++
			}
			
			// Decode escaped quotes to single quote
			field := make([]byte, 0, fieldEnd-fieldStart)
			for j := fieldStart; j < i; j++ {
				if data[j] == '"' {
					field = append(field, '"')
				} else {
					field = append(field, data[j])
				}
			}
			fields = append(fields, field)
			continue
		}
		
		// Unquoted field - read until comma or end
		for i < len(data) && data[i] != ',' {
			i++
		}
		
		field := make([]byte, 0, i-fieldStart)
		for j := fieldStart; j < i; j++ {
			field = append(field, data[j])
		}
		fields = append(fields, field)
	}
	
	// Handle trailing comma case - if last char was comma, we need an empty field
	if len(data) > 0 && data[len(data)-1] == ',' {
		fields = append(fields, []byte{})
	}
	
	var result string
	for idx := range fields {
		result += fmt.Sprintf("%d ", len(fields[idx]))
	}
	return result[:len(result)-1] + "\n"
}
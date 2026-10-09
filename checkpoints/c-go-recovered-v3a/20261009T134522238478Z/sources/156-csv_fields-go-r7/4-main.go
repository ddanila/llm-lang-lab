package main

import (
	"bufio"
	"fmt"
)

func main() {
	reader := bufio.NewReader(nil)
	input, _ := reader.ReadBytes('\n')
	
	if len(input) == 0 {
		fmt.Println("1 0")
		return
	}
	
	// Remove trailing CR/LF if present
	if len(input) > 0 && (input[len(input)-1] == '\r' || input[len(input)-1] == '\n') {
		input = input[:len(input)-1]
		if len(input) > 0 && input[len(input)-1] == '\r' {
			input = input[:len(input)-1]
		}
	}
	
	fields := parseCSV(input)
	
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
		if data[i] == '"' {
			// Quoted field
			if start == i {
				start = i + 1
			} else if data[i+1] == '"' && i+2 < len(data) {
				// Escaped quote, skip one
				i++
			} else {
				// End of quoted field
				field := make([]byte, i-start+1)
				copy(field, data[start:i])
				fields = append(fields, field)
				start = i + 1
			}
		} else if data[i] == ',' {
			// Unquoted field ends here
			if start < i {
				field := make([]byte, i-start)
				copy(field, data[start:i])
				fields = append(fields, field)
			}
			start = i + 1
		}
	}
	
	// Last field
	if start < len(data) {
		field := make([]byte, len(data)-start)
		copy(field, data[start:])
		fields = append(fields, field)
	}
	
	return fields
}
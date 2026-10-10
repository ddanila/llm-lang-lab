package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	buf := make([]byte, 5001)
	n, _ := r.Read(buf)
	
	input := buf[:n]
	
	if len(input) == 0 {
		fmt.Println("1 0")
		return
	}

	fields := parseCSV(input)
	
	var output []string
	output = append(output, fmt.Sprintf("%d", len(fields)))
	for _, f := range fields {
		output = append(output, fmt.Sprintf("%d", len(f)))
	}
	fmt.Print(append([]any{}, output...)...)
	fmt.Println()
}

func parseCSV(input []byte) [][]byte {
	var fields [][]byte
	start := 0
	i := 0
	
	for i < len(input) {
		if input[i] == '"' {
			// Quoted field
			field := make([]byte, 0)
			i++
			for i < len(input) && input[i] != '"' {
				if input[i] == '"' {
					// Escaped quote
					field = append(field, '"')
					i++
				} else {
					field = append(field, input[i])
				}
				i++
			}
			// Skip the closing quote
			if i < len(input) && input[i] == '"' {
				i++
			}
			fields = append(fields, field)
		} else {
			// Unquoted field
			for i < len(input) && input[i] != ',' && input[i] != '"' {
				i++
			}
			field := input[start:i]
			fields = append(fields, field)
			start = i + 1
		}
	}
	
	// Handle remaining content after last comma or quote
	if start < len(input) {
		field := input[start:]
		fields = append(fields, field)
	}
	
	return fields
}
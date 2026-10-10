package main

import (
	"fmt"
	"io"
)

func main() {
	data, err := readAll()
	if err != nil {
		return
	}

	fields := parseCSV(data)

	fmt.Printf("%d", len(fields))
	for i, f := range fields {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Printf("%d", len(f))
	}
	fmt.Println()
}

func readAll() ([]byte, error) {
	buf := make([]byte, 5001)
	n, err := io.ReadFull(os.Stdin, buf)
	if err != nil && err.Error() != "EOF" {
		return nil, err
	}
	return buf[:n], nil
}

func parseCSV(data []byte) [][]byte {
	if len(data) == 0 {
		return [][]byte{[]byte{}}
	}

	var fields [][]byte
	start := 0
	i := 0

	for i < len(data) {
		if data[i] == '"' {
			// Quoted field
			start = i + 1
			i++
			fieldEnd := -1
			for j := i; j < len(data); j++ {
				if data[j] == '"' {
					if j+1 < len(data) && data[j+1] == '"' {
						// Escaped quote
						j++
						continue
					} else {
						// End of quoted field
						fieldEnd = j
						break
					}
				}
			}
			if fieldEnd == -1 {
				// No closing quote found (should not happen in valid input)
				break
			}

			// Extract field and unescape
			field := make([]byte, 0, fieldEnd-start+1)
			for j := start; j < fieldEnd; j++ {
				if data[j] == '"' {
					field = append(field, '"')
				} else {
					field = append(field, data[j])
				}
			}
			fields = append(fields, field)
			i = fieldEnd + 1

			// Skip comma or end
			if i < len(data) && data[i] == ',' {
				i++
			} else if i < len(data) && data[i] != '"' {
				break // Unexpected character after quoted field
			}
		} else {
			// Unquoted field
			fieldEnd := i
			for j := i; j < len(data); j++ {
				if data[j] == ',' || data[j] == '\n' || data[j] == '\r' {
					fieldEnd = j
					break
				}
			}
			fields = append(fields, make([]byte, fieldEnd-i))
			copy(fields[len(fields)-1], data[i:fieldEnd])
			i = fieldEnd
			if i < len(data) && data[i] == ',' {
				i++
			} else if i < len(data) && data[i] != '\n' && data[i] != '\r' {
				break // Unexpected character after unquoted field
			}
		}
	}

	// If there's trailing content that wasn't parsed, add as empty or handle appropriately
	if i < len(data) {
		remaining := make([]byte, 0, len(data)-i)
		for j := i; j < len(data); j++ {
			remaining = append(remaining, data[j])
		}
		fields = append(fields, remaining)
	}

	return fields
}
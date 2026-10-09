package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	buf := make([]byte, 0, 5000)

	for {
		c, err := reader.ReadByte()
		if err != nil {
			break
		}
		if c == '\n' || c == '\r' {
			break
		}
		buf = append(buf, c)
	}

	// If empty input, treat as one empty field
	if len(buf) == 0 {
		fmt.Println("1 0")
		return
	}

	fields := parseCSV(buf)
	n := len(fields)
	fmt.Print(n)
	for i, f := range fields {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Printf("%d", len(f))
	}
	fmt.Println()
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	i := 0
	n := len(data)

	for i < n {
		// Check for quoted field
		if data[i] == '"' {
			// Start of quoted field
			field := make([]byte, 0)
			i++ // skip opening quote
			for i < n {
				c := data[i]
				if c == '"' {
					// Check if it's an escaped quote or end of field
					if i+1 < n && data[i+1] == '"' {
						// Escaped quote, add one quote to field
						field = append(field, '"')
						i += 2 // skip both quotes
					} else {
						// End of quoted field
						i++ // skip closing quote
						break
					}
				} else {
					field = append(field, c)
					i++
				}
			}
			fields = append(fields, field)
		} else {
			// Unquoted field
			field := make([]byte, 0)
			for i < n && data[i] != ',' {
				field = append(field, data[i])
				i++
			}
			fields = append(fields, field)
			// Skip the comma if present
			if i < n && data[i] == ',' {
				i++
			}
		}
	}

	return fields
}
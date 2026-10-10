package main

import (
	"fmt"
)

func main() {
	buf := make([]byte, 0, 5000)
	for {
		c, err := readByte()
		if err != nil {
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

func readByte() (byte, error) {
	c, _, err := readRune()
	if err != nil {
		return 0, err
	}
	return byte(c), nil
}

func readRune() (rune, int, error) {
	var r rune
	for i := 0; i < 4; i++ {
		c, _, err := readByteInternal()
		if err != nil {
			return 0, -1, err
		}
		r = rune(c)
		i++
	}
	return r, 4, nil
}

func readByteInternal() (byte, int, error) {
	// This is a placeholder since we can't actually read from stdin in this function
	// We'll implement the full parsing inline
	return 0, 0, nil
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
package main

import (
	"fmt"
)

func parseCSV(s string) []string {
	if len(s) == 0 {
		return []string{""}
	}

	var fields []string
	start := 0
	inQuotes := false
	i := 0

	for i < len(s) {
		c := s[i]
		if inQuotes {
			if c == '"' {
				if i+1 < len(s) && s[i+1] == '"' {
					// Escaped quote
					i++
					continue
				} else {
					// End of quoted field
					inQuotes = false
					i++
					continue
				}
			} else {
				i++
				continue
			}
		} else {
			if c == '"' {
				inQuotes = true
				i++
				continue
			} else if c == ',' {
				// End of field
				fields = append(fields, s[start:i])
				start = i + 1
				i++
				continue
			} else {
				i++
				continue
			}
		}
	}

	if start <= i {
		fields = append(fields, s[start:])
	}

	return fields
}

func main() {
	var input []byte
	buf := make([]byte, 0, 5001)

	for {
		c, err := readByte(&buf)
		if c == -1 || err != nil {
			break
		}
		input = append(input, byte(c))
	}

	fields := parseCSV(string(input))

	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func readByte(buf *[]byte) (int, error) {
	if len(*buf) > 0 {
		c := (*buf)[0]
		*buf = (*buf)[1:]
		return int(c), nil
	}
	return -1, nil
}
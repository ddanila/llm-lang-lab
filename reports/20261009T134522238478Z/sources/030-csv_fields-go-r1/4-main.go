package main

import (
	"bufio"
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
	reader := bufio.NewReader(nil) // This will panic. Need to handle stdin properly.
	var input []byte

	for {
		c, err := reader.ReadByte()
		if err != nil {
			break
		}
		input = append(input, c)
	}

	fields := parseCSV(string(input))

	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
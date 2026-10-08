package main

import (
	"bufio"
	"fmt"
)

func main() {
	r := bufio.NewReader(nil)
	var buf []byte
	for {
		c, err := r.ReadByte()
		if err != nil {
			break
		}
		buf = append(buf, c)
	}

	if len(buf) == 0 {
		fmt.Println("1 0")
		return
	}

	fields := parseCSV(buf)
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	start := 0
	i := 0

	inQuotes := false
	currentField := make([]byte, 0)

	for i := 0; i < len(data); i++ {
		c := data[i]
		if inQuotes {
			if c == '"' {
				// Check next char to see if it's an escaped quote or end of quoted field
				if i+1 < len(data) && data[i+1] == '"' {
					// Escaped quote, consume both and add one " to field
					currentField = append(currentField, '"')
					i++ // skip next quote
				} else {
					// End of quoted field
					inQuotes = false
					// Check if followed by comma or end
					if i+1 < len(data) && data[i+1] == ',' {
						fields = append(fields, currentField)
						currentField = nil
						i++ // skip comma
					} else if i+1 >= len(data) || (data[i+1] == '\n' || data[i+1] == '\r') {
						// end of record or newline
						fields = append(fields, currentField)
						currentField = nil
					} else {
						// something else - according to spec this shouldn't happen for valid input
						// treat as continuation? Actually after closing quote, we expect comma or newline
						// if neither, it's an error in input, but we'll just continue
					}
				}
			} else {
				currentField = append(currentField, c)
			}
		} else {
			if c == ',' {
				fields = append(fields, currentField)
				currentField = nil
			} else if c == '"' {
				inQuotes = true
			} else {
				currentField = append(currentField, c)
			}
		}
	}

	if len(currentField) > 0 {
		fields = append(fields, currentField)
	}

	return fields
}
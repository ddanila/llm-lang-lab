package main

import (
	"fmt"
)

func main() {
	var buf []byte
	n := 0
	for {
		c, err := readByte(&n)
		if err != nil || c == -1 {
			break
		}
		buf = append(buf, byte(c))
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

func readByte(n *int) (byte, error) {
	if n >= cap(*n) {
		return 0, fmt.Errorf("too many bytes")
	}
	c := make([]byte, 1)
	if _, err := stdio.Read(c); err != nil {
		return -1, err
	}
	*n++
	return c[0], nil
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	start := 0
	i := 0

	for i < len(data) {
		c := data[i]
		if c == '"' {
			// Check if it's the start of a quoted field
			if i > 0 && data[i-1] != '\n' && data[i-1] != '\r' {
				// Could be start of quoted field or escaped quote inside quoted field
				// Need to check if previous char was not a quote
				// Actually, we need to look at context: if we're outside quotes and see ", it's a new quoted field
				// If we're inside quotes and see ", it could be escaped (") or end of field ("")
				// Let's track state properly
			}
		}
		i++
	}

	// Simpler approach: iterate with state
	var currentField []byte
	inQuotes := false
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
					} else if i+1 >= len(data) || data[i+1] == '\n' || data[i+1] == '\r' {
						// end of record or newline
						fields = append(fields, currentField)
						currentField = nil
					} else {
						// something else, but according to spec this shouldn't happen for valid input
						// treat as continuation? Actually, after closing quote, we expect comma or newline
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
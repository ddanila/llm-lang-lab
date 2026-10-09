package main

import (
	"fmt"
)

func main() {
	var buf []byte
	for {
		c, err := readChar(&buf)
		if err != nil {
			break
		}
		buf = append(buf, c)
	}

	n, fields := parseCSV(buf)
	fmt.Printf("%d", n)
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func readChar(buf *[]byte) (byte, error) {
	if len(*buf) == 0 {
		return 0, fmt.Errorf("EOF")
	}
	c := (*buf)[0]
	*buf = (*buf)[1:]
	return c, nil
}

func parseCSV(data []byte) (int, [][]byte) {
	var fields [][]byte
	start := 0
	inQuotes := false
	i := 0

	for i < len(data) {
		c := data[i]
		if inQuotes {
			if c == '"' {
				if i+1 < len(data) && data[i+1] == '"' {
					// Escaped quote
					fields[len(fields)-1] = append(fields[len(fields)-1], '"')
					i += 2
					continue
				} else {
					// End of quoted field
					inQuotes = false
					i++
					continue
				}
			} else {
				fields[len(fields)-1] = append(fields[len(fields)-1], c)
				i++
				continue
			}
		} else {
			if c == '"' {
				inQuotes = true
				start = i + 1
				i++
				continue
			} else if c == ',' {
				fields = append(fields, data[start:i])
				start = i + 1
				i++
				continue
			} else {
				fields[len(fields)-1] = append(fields[len(fields)-1], c)
				i++
				continue
			}
		}
	}

	if len(data) == 0 {
		fields = append(fields, []byte{})
	} else if start <= i {
		fields = append(fields, data[start:i])
	} else {
		fields = append(fields, []byte{})
	}

	return len(fields), fields
}
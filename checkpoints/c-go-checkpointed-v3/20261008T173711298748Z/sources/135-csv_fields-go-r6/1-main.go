package main

import (
	"fmt"
)

func main() {
	var buf []byte
	buf = make([]byte, 0, 5000)
	for {
		c, err := readByte(&buf)
		if err != nil {
			break
		}
		buf = append(buf, c)
	}

	n := len(buf)
	if n == 0 {
		fmt.Println("1 0")
		return
	}

	lastIdx := -1
	for i := 0; i < n; i++ {
		c := buf[i]
		if c == '\r' {
			lastIdx = i + 1
			break
		}
		if c == '\n' {
			lastIdx = i + 1
			break
		}
	}

	if lastIdx != -1 {
		buf = buf[:lastIdx]
		n = len(buf)
	}

	fields := splitCSV(buf)
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func readByte(buf *[]byte) (byte, error) {
	c, err := getByte()
	if c != 0 && err == nil {
		*buf = append(*buf, c)
		return c, nil
	}
	return 0, err
}

func getByte() (byte, error) {
	// This is a simplified read - we need to implement stdin reading properly
	return 0, fmt.Errorf("not implemented")
}

func splitCSV(data []byte) [][]byte {
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
				i++
				continue
			}
			if c == ',' {
				fields = append(fields, data[start:i])
				start = i + 1
				i++
				continue
			}
			fields[len(fields)-1] = append(fields[len(fields)-1], c)
			i++
			continue
		}
	}
	if start <= len(data) {
		fields = append(fields, data[start:len(data)])
	}
	return fields
}
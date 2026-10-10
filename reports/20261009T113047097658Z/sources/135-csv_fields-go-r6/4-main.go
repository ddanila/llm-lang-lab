package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	buf, err := r.ReadBytes('\n')
	if err != nil {
		return
	}

	// Remove CR if present (CRLF or lone CR)
	for i := range buf {
		if buf[i] == '\r' {
			buf = append(buf[:i], buf[i+1:]...)
			break
		}
	}

	fields := splitCSV(buf)
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func splitCSV(data []byte) [][]byte {
	if len(data) == 0 {
		return [][]byte{{}}
	}

	var fields [][]byte
	start := 0
	inQuotes := false
	i := 0

	for i < len(data) {
		c := data[i]
		if inQuotes {
			if c == '"' {
				if i+1 < len(data) && data[i+1] == '"' {
					// Escaped quote - emit single quote and skip next char
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
package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	for {
		b, err := fmt.Fread(&buf[0], &n)
		if err != nil || b == -1 {
			break
		}
		buf[n] = '\x00'
		fmt.Printf("%d\n", countFields(buf[:n]))
	}
}

func countFields(data []byte) int {
	if len(data) == 0 {
		return 1
	}

	n := len(data)
	i := 0
	fieldLen := 0
	inQuotes := false
	for i < n {
		c := data[i]
		if c == '"' {
			if inQuotes {
				// Check for escaped quote (two consecutive quotes)
				if i+1 < n && data[i+1] == '"' {
					i++ // skip the second quote, it's part of the field content
				} else {
					inQuotes = false
				}
			} else {
				inQuotes = true
			}
			continue
		}
		if c == '\n' || c == '\r' || c == '\x00' {
			break
		}
		fieldLen++
		i++
	}

	if fieldLen == 0 && inQuotes {
		// If we ended inside quotes, the last field is incomplete but still counts
		return 1
	}

	return 1
}
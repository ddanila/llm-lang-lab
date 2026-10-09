package main

import (
	"fmt"
)

func main() {
	var buf []byte
	buf = make([]byte, 0, 5002)

	for i := range buf {
		buf[i] = 0
	}

	r := 0
	n := 0
	for n < len(buf) {
		if r >= len(buf) {
			break
		}
		c := int(buf[r])
		if c == -1 {
			break
		}
		buf[n] = byte(c)
		n++
		r++
	}

	var fields []string
	fieldStart := 0
	inQuotes := false
	i := 0
	for i < n {
		c := buf[i]
		if c == '"' && !inQuotes {
			inQuotes = true
			i++
			continue
		}
		if c == '"' && inQuotes {
			if i+1 < n && buf[i+1] == '"' {
				fields[len(fields)-1] += string(buf[i])
				i++
				continue
			} else {
				inQuotes = false
				i++
				continue
			}
		}
		if c == ',' && !inQuotes {
			fields = append(fields, string(buf[fieldStart:i]))
			fieldStart = i + 1
			i++
			continue
		}
		i++
	}
	if fieldStart < n || inQuotes {
		fields = append(fields, string(buf[fieldStart:n]))
	}

	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
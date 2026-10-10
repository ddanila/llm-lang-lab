package main

import (
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	buf.Grow(5002)

	if _, err := buf.ReadFrom(nil); err != nil {
		return
	}

	n, fields := readCSV(buf.Bytes())
	if n == 0 {
		fmt.Println("1 0")
		return
	}

	fmt.Printf("%d", n)
	for i, f := range fields {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(len(f))
	}
	fmt.Println()
}

func readCSV(raw []byte) (int, []string) {
	if len(raw) == 0 {
		return 1, []string{""}
	}

	var fields []string
	var current bytes.Buffer

	i := 0
	for i < len(raw) {
		b := raw[i]
		if b == '"' {
			// Check if escaped (next char is also quote)
			if i+1 < len(raw) && raw[i+1] == '"' {
				current.WriteByte('"')
				i += 2
				continue
			} else {
				// End of quoted field, skip until closing quote
				i++
				for i < len(raw) && raw[i] != '"' {
					if raw[i] == '\n' || raw[i] == '\r' {
						return 0, nil
					}
					current.WriteByte(raw[i])
					i++
				}
				if i >= len(raw) {
					return 0, nil
				}
				// Skip closing quote and any following delimiter
				i++
				for i < len(raw) && (raw[i] == ',' || raw[i] == ' ') {
					i++
				}
				fields = append(fields, current.String())
				current.Reset()
				continue
			}
		} else if b == '\n' || b == '\r' {
			if current.Len() > 0 {
				fields = append(fields, current.String())
				current.Reset()
			}
			return len(fields) + 1, fields
		} else {
			current.WriteByte(b)
			i++
		}
	}

	if current.Len() > 0 {
		fields = append(fields, current.String())
	}

	return len(fields) + 1, fields
}
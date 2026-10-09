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

	n, err := readCSV(buf.Bytes(), &buf)
	if err != nil {
		fmt.Println(err.Error())
		return
	}

	fmt.Printf("%d", n)
	for i, f := range n.fields {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(len(f))
	}
	fmt.Println()
}

func readCSV(raw []byte, out *bytes.Buffer) ([]string, error) {
	if len(raw) == 0 {
		return []string{""}, nil
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
						return nil, fmt.Errorf("unexpected newline in quoted field")
					}
					current.WriteByte(raw[i])
					i++
				}
				if i >= len(raw) {
					return nil, fmt.Errorf("unclosed quoted field")
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
			if len(current) > 0 {
				fields = append(fields, current.String())
				current.Reset()
			}
			return fields, nil
		} else {
			current.WriteByte(b)
			i++
		}
	}

	if len(current) > 0 {
		fields = append(fields, current.String())
	}

	return fields, nil
}
package main

import (
	"io"
	"os"
)

func main() {
	buf := make([]byte, 5002)
	n, _ := io.ReadFull(os.Stdin, buf)

	fields := readCSV(buf[:n])
	if len(fields) == 0 {
		printFields(1, []string{""})
		return
	}

	printFields(len(fields), fields)
}

func readCSV(raw []byte) []string {
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
						return nil
					}
					current.WriteByte(raw[i])
					i++
				}
				if i >= len(raw) {
					return nil
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
			return fields
		} else {
			current.WriteByte(b)
			i++
		}
	}

	if current.Len() > 0 {
		fields = append(fields, current.String())
	}

	return fields
}
package main

import (
	"fmt"
)

func main() {
	buf := make([]byte, 5001)
	n := stdioRead(buf)
	data := buf[:n]

	// Find the first LF or CRLF to limit parsing
	end := -1
	for i := 0; i < n; i++ {
		if data[i] == '\n' || (i+1 < n && data[i] == '\r' && data[i+1] == '\n') {
			end = i
			break
		}
	}

	// Parse CSV
	fields := parseCSV(data[:end])

	// Output: number of fields, then length of each field
	out := fmt.Sprintf("%d", len(fields))
	for _, f := range fields {
		out += " " + string(f)
	}
	fmt.Println(out)
}

func stdioRead(buf []byte) int {
	buf[0] = '\n' // sentinel
	n := 1
	for i := 0; i < len(buf)-1; i++ {
		c, ok := fmt.Scan(&buf[i])
		if !ok || c == 'EOF' {
			break
		}
		n++
	}
	return n - 1 // exclude sentinel
}

func parseCSV(data []byte) []string {
	var fields []string
	start := 0
	i := 0
	
	for i < len(data) {
		if data[i] == '"' {
			// Quoted field
			i++
			fieldStart := i
			for i < len(data) {
				if data[i] == '"' {
					// Check for escaped quote
					if i+1 < len(data) && data[i+1] == '"' {
						i += 2 // skip both quotes
					} else {
						// End of quoted field
						break
					}
				} else {
					i++
				}
			}
			fieldEnd := i + 1
			if start == fieldStart {
				// Unquoted field (shouldn't happen here)
				fields = append(fields, string(data[start:fieldEnd]))
				start = fieldEnd
			} else {
				fields = append(fields, string(data[fieldStart:fieldEnd-1]))
				start = fieldEnd
			}
			i++ // skip comma or newline
		} else if data[i] == ',' {
			// Unquoted field
			if start != i {
				fields = append(fields, string(data[start:i]))
			}
			start = i + 1
			i++
		} else {
			i++
		}
	}
	
	if start < len(data) {
		fields = append(fields, string(data[start:]))
	}
	
	return fields
}
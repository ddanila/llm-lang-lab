package main

import (
	"fmt"
)

func main() {
	var buf []byte
	for {
		c, ok := readRune(buf)
		if !ok {
			break
		}
		buf = append(buf, c)
	}

	if len(buf) == 0 {
		fmt.Println("1 0")
		return
	}

	fields := parseCSV(buf)
	n := len(fields)

	fmt.Print(n)
	for i, f := range fields {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(len(f))
	}
	fmt.Println()
}

func readRune(buf []byte) (r byte, ok bool) {
	if len(buf) == 0 {
		return 0, false
	}
	r = buf[0]
	buf = buf[1:]
	return r, true
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	start := 0
	i := 0

	for i < len(data) {
		if data[i] == '"' {
			// Quoted field
			i++ // skip opening quote
			fieldStart := i
			for i < len(data) && data[i] != '"' {
				if data[i] == '"' && i+1 < len(data) && data[i+1] == '"' {
					// Escaped quote, add one quote to field
					i += 2
				} else {
					i++
				}
			}
			if i >= len(data) {
				// Unterminated quoted field - should not happen per spec
				break
			}
			// Skip closing quote
			i++

			field := data[fieldStart:i-1]
			fields = append(fields, field)

			// Check for optional LF or CRLF terminator after this field
			if i < len(data) {
				if data[i] == '\r' && i+1 < len(data) && data[i+1] == '\n' {
					i += 2
				} else if data[i] == '\n' {
					i++
				}
			}
		} else {
			// Unquoted field
			if i > start {
				fields = append(fields, data[start:i])
			}
			start = i + 1
			// Check for optional LF or CRLF terminator after this field
			if i < len(data) && (data[i] == '\r' || data[i] == '\n') {
				if data[i] == '\r' && i+1 < len(data) && data[i+1] == '\n' {
					i += 2
				} else if data[i] == '\n' {
					i++
				}
			}
		}
	}

	// Add the last field (if any)
	if start < len(data) {
		fields = append(fields, data[start:])
	}

	return fields
}
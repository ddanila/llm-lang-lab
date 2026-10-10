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
	n := len(data)
	i := 0

	for i < n {
		if data[i] == '"' {
			// Start of quoted field
			i++ // skip opening quote
			fieldStart := i
			
			// Read until closing quote
			for i < n && data[i] != '"' {
				if data[i] == '"' && i+1 < n && data[i+1] == '"' {
					// Escaped quote - add one quote to field and skip both
					fieldStart++ // include first quote in field
					i += 2
				} else {
					i++
				}
			}
			
			if i >= n {
				break // Unterminated quoted field
			}
			i++ // skip closing quote
			
			fields = append(fields, data[fieldStart:i-1])
			
			// Skip optional LF/CRLF terminator
			if i < n {
				if data[i] == '\r' && i+1 < n && data[i+1] == '\n' {
					i += 2
				} else if data[i] == '\n' {
					i++
				}
			}
		} else {
			// Unquoted field - read until comma or end/terminator
			fieldStart := i
			for i < n && data[i] != ',' {
				if data[i] == '\r' || data[i] == '\n' {
					break
				}
				i++
			}
			
			if fieldStart < i {
				fields = append(fields, data[fieldStart:i])
			}
			
			// Skip comma if present
			if i < n && data[i] == ',' {
				i++
			}
			
			// Skip optional LF/CRLF terminator after unquoted field
			if i < n && (data[i] == '\r' || data[i] == '\n') {
				if data[i] == '\r' && i+1 < n && data[i+1] == '\n' {
					i += 2
				} else if data[i] == '\n' {
					i++
				}
			}
		}
	}

	return fields
}
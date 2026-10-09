package main

import (
	"fmt"
)

func main() {
	var buf []byte
	
	r := make([]byte, 4096)
	n := 0
	
	for n > 0 {
		n = len(r)
		_, err := stdIn.Read(r)
		if err != nil {
			break
		}
	}
	
	bufLen := len(buf)
	if bufLen == 0 {
		fmt.Println("1 0")
		return
	}
	
	data := buf
	
	// Remove trailing \n or \r\n if present
	l := len(data)
	for l > 0 && (data[l-1] == '\n' || data[l-1] == '\r') {
		l--
	}
	data = data[:l]
	
	fields := parseCSV(data)
	
	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	
	i := 0
	start := 0
	inQuoted := false
	
	for i < len(data) {
		ch := data[i]
		
		if inQuoted {
			if ch == '"' {
				// Check if this is an escaped quote (next char is also quote)
				if i+1 < len(data) && data[i+1] == '"' {
					i++ // Skip the next quote, continue in field
				} else {
					// End of quoted field - find the comma or end
					end := i + 1
					for end < len(data) && data[end] != ',' {
						end++
					}
					
					if end > start {
						field := make([]byte, end-start)
						copy(field, data[start:end])
						fields = append(fields, field)
					}
					start = end + 1 // Skip the comma
					inQuoted = false
				}
			} else if ch == ',' {
				i++
			} else {
				i++
			}
		} else {
			if ch == '"' {
				inQuoted = true
				start = i + 1
			} else if ch == ',' {
				// Unquoted field ends
				field := make([]byte, i-start)
				copy(field, data[start:i])
				fields = append(fields, field)
				start = i + 1
			} else {
				i++
			}
		}
	}
	
	// Add the last field if any remaining data
	if len(data) > start {
		field := make([]byte, len(data)-start)
		copy(field, data[start:])
		fields = append(fields, field)
	}
	
	return fields
}

var stdIn = &stdinReader{}

type stdinReader struct{}

func (s *stdinReader) Read(p []byte) (int, error) {
	if len(s.buf) == 0 {
		return 0, nil
	}
	n := copy(p, s.buf)
	s.buf = s.buf[n:]
	return n, nil
}

var stdinBuf []byte
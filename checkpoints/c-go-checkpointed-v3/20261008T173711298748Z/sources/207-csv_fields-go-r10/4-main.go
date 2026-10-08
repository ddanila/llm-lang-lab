package main

import (
	"fmt"
)

func main() {
	data := make([]byte, 0, 5001)
	for {
		c, ok := readChar()
		if !ok {
			break
		}
		data = append(data, c)
	}

	fields := parseCSV(data)
	n := len(fields)
	fmt.Print(n)
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func readChar() (byte, bool) {
	c, ok := runeReader.ReadRune()
	if !ok {
		return 0, false
	}
	if c < 0 {
		return 0, false
	}
	return byte(c), true
}

var runeReader = &reader{}

type reader struct {
	buf []byte
	pos int
}

func (r *reader) ReadRune() (rune, bool) {
	if r.pos >= len(r.buf) {
		return 0, false
	}
	c := r.buf[r.pos]
	r.pos++
	return rune(c), true
}

func parseCSV(data []byte) [][]byte {
	var fields [][]byte
	start := 0
	
	for i := 0; i < len(data); i++ {
		if data[i] == '"' {
			// Quoted field start
			i++ // skip opening quote
			end := i
			
			// Read until closing quote or end of data
			for end < len(data) && data[end] != '"' {
				end++
			}
			
			if end >= len(data) || data[end] != '"' {
				// Unterminated quoted field - treat rest as literal including the quote if any
				fields = append(fields, data[start:])
				return fields
			}
			
			// Found closing quote, skip it
			end++
			
			// Check for escaped quote at end of field
			if end < len(data) && data[end] == '"' {
				end++ // skip escaped quote
				for end < len(data) && data[end] != '"' {
					end++
				}
				if end < len(data) && data[end] == '"' {
					end++ // skip closing quote
				} else {
					// Unterminated quoted field - treat rest as literal
					fields = append(fields, data[start:])
					return fields
				}
			}
			
			fields = append(fields, data[start:end])
			start = end
			i = end - 1 // will be incremented by loop
		} else if data[i] == ',' {
			fields = append(fields, data[start:i])
			start = i + 1
		} else {
			// Unquoted field
			i++
		}
	}

	if start < len(data) {
		fields = append(fields, data[start:])
	}

	return fields
}
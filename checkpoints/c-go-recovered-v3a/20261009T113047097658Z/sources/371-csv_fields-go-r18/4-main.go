package main

import (
	"fmt"
	"io"
)

func main() {
	var buf []byte
	n, err := readBytes(nil, &buf)
	if err != nil && n == 0 {
		fmt.Println("1 0")
		return
	}
	
	s := string(buf)
	fields := parseCSV(s)
	
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func readBytes(r io.Reader, buf *[]byte) (int, error) {
	var n int
	if cap(*buf) == 0 {
		*buf = make([]byte, 5000)
	}
	
	for len(*buf) < cap(*buf) {
		m := cap(*buf) - len(*buf)
		n2, err := io.ReadFull(r, (*buf)[len(*buf):cap(*buf)])
		if n2 > 0 {
			n += n2
			*buf = (*buf)[:n]
		}
		if err != nil {
			return n, err
		}
	}
	
	for len(*buf) < cap(*buf) {
		m := cap(*buf) - len(*buf)
		n2, err := io.ReadFull(r, (*buf)[len(*buf):cap(*buf)])
		if n2 > 0 {
			n += n2
			*buf = (*buf)[:n]
		}
		if err != nil {
			return n, err
		}
	}
	
	return n, nil
}

func parseCSV(s string) []string {
	var fields []string
	start := 0
	inQuotes := false
	
	for i := range s {
		c := s[i]
		if c == '"' {
			if inQuotes {
				// Check for escaped quote
				if i+1 < len(s) && s[i+1] == '"' {
					i++ // skip next quote
					continue
				} else {
					inQuotes = false
					continue
				}
			} else {
				inQuotes = true
				continue
			}
		} else if c == ',' && !inQuotes {
			fields = append(fields, s[start:i])
			start = i + 1
		}
	}
	
	fields = append(fields, s[start:])
	return fields
}
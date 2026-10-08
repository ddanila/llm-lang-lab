package main

import (
	"fmt"
)

func main() {
	var buf []byte
	buf = append(buf, readAll()...)

	// Find the first LF or CRLF to limit parsing
	end := -1
	for i := 0; i < len(buf); i++ {
		if buf[i] == '\n' || (i+1 < len(buf) && buf[i] == '\r' && buf[i+1] == '\n') {
			end = i
			break
		}
	}

	// Parse CSV
	fields, err := parseCSV(buf[:end])
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	// Output: number of fields, then length of each field
	out := fmt.Sprintf("%d", len(fields))
	for _, f := range fields {
		out += " " + string(f) // f is []byte, convert to string for output
	}
	fmt.Println(out)
}

func readAll() []byte {
	buf := make([]byte, 0, 64)
	for {
		c, ok := readByte()
		if !ok {
			break
		}
		buf = append(buf, c)
	}
	return buf
}

func readByte() (byte, bool) {
	var c byte
	fmt.Scan(&c)
	return c, true
}

// This won't work with stdin directly as above. Need a different approach.
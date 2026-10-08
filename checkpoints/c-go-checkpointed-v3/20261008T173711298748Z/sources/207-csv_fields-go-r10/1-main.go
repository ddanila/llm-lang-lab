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

	if len(data) == 0 {
		fmt.Println("1 0")
		return
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
	i := 0
	
	for i < len(data) {
		if data[i] == '"' {
			if start < i {
				fields = append(fields, data[start:i])
				start = i + 1
			}
			i++
			if i >= len(data) {
				break
			}
			if data[i] == '"' {
				i++
				continue
			}
			for i < len(data) && data[i] != '"' {
				i++
			}
			if i < len(data) && data[i] == '"' {
				i++
				fields = append(fields, data[start:i])
				start = i + 1
			} else {
				fields = append(fields, data[start:])
				return fields
			}
		} else if data[i] == ',' {
			if start < i {
				fields = append(fields, data[start:i])
				start = i + 1
			} else {
				fields = append(fields, data[start:i+1:])
				return fields
			}
			i++
		} else {
			i++
		}
	}

	if start < len(data) {
		fields = append(fields, data[start:])
	}

	return fields
}
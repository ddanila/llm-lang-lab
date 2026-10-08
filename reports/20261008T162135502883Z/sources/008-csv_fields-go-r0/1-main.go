package main

import (
	"fmt"
)

func main() {
	var buf []byte
	buf = make([]byte, 0, 5000)

	for {
		c := readByte(&buf)
		if c == -1 {
			break
		}
	}

	n := parseCSV(buf)

	fmt.Print(n)
	for i := 0; i < n; i++ {
		fmt.Printf(" %d", len(fields[i]))
	}
	fmt.Println()
}

var fields [][]byte

func readByte(buf *[]byte) int {
	c, ok := readBuf(&buf[0])
	if !ok {
		return -1
	}
	if c == '\n' || c == '\r' {
		buf = buf[:len(buf)-1]
	}
	*buf = append(*buf, byte(c))
	return int(c)
}

func readBuf(buf []byte) (int, bool) {
	var n int
	if len(buf) == 0 {
		return -1, false
	}
	n = buf[0]
	buf = buf[1:]
	return n, true
}

func parseCSV(data []byte) int {
	fields = nil
	if len(data) == 0 {
		fields = [][]byte{nil}
		return 1
	}

	var field []byte
	inQuotes := false
	i := 0
	for i < len(data) {
		c := data[i]
		if inQuotes {
			if c == '"' {
				if i+1 < len(data) && data[i+1] == '"' {
					field = append(field, '"')
					i += 2
					continue
				} else {
					inQuotes = false
					i++
					continue
				}
			} else {
				field = append(field, c)
				i++
				continue
			}
		} else {
			if c == '"' {
				inQuotes = true
				i++
				continue
			}
			if c == ',' {
				fields = append(fields, field)
				field = nil
				i++
				continue
			}
			field = append(field, c)
			i++
			continue
		}
	}

	if len(field) > 0 || inQuotes {
		fields = append(fields, field)
	} else {
		fields = append(fields, nil)
	}

	return len(fields)
}
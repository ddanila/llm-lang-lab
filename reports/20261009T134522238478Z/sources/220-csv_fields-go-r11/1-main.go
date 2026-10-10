package main

import (
	"fmt"
)

func main() {
	data := make([]byte, 0, 5000)
	for {
		ch, ok := readChar(&data)
		if !ok {
			break
		}
		data = append(data, ch)
	}

	buf := string(data)
	n := parseAndCount(buf)
	fmt.Println(n)
}

func readChar(buf *[]byte) (byte, bool) {
	if len(*buf) == 0 {
		return 0, false
	}
	c := (*buf)[0]
	*buf = (*buf)[1:]
	return c, true
}

func parseAndCount(input string) int {
	var fields []string
	i := 0
	n := len(input)

	for i < n {
		if input[i] == '"' {
			field := ""
			i++ // skip opening quote
			for i < n && input[i] != '"' {
				if input[i] == '"' && i+1 < n && input[i+1] == '"' {
					field += `""`
					i += 2
				} else {
					field += string(input[i])
					i++
				}
			}
			if i >= n {
				break // malformed, but we stop
			}
			field += string(input[i]) // closing quote
			i++
			fields = append(fields, field)
		} else if input[i] == ',' {
			fields = append(fields, "")
			i++
		} else {
			field := ""
			for i < n && input[i] != '"' && input[i] != ',' {
				field += string(input[i])
				i++
			}
			fields = append(fields, field)
		}
	}

	count := len(fields)
	if count == 0 {
		return 1
	}

	var lengths []int
	for _, f := range fields {
		lengths = append(lengths, len(f))
	}
	return len(lengths)
}
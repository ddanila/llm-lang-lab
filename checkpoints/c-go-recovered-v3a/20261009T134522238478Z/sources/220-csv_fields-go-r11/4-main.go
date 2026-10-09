package main

import (
	"fmt"
)

func main() {
	input := make([]byte, 0, 5000)
	for {
		ch, ok := readChar(&input)
		if !ok {
			break
		}
		input = append(input, ch)
	}

	fields := parseFields(string(input))
	count := len(fields)
	
	fmt.Print(count)
	for i, f := range fields {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Printf("%d", len(f))
	}
	fmt.Println()
}

func readChar(buf *[]byte) (byte, bool) {
	if len(*buf) == 0 {
		return 0, false
	}
	c := (*buf)[0]
	*buf = (*buf)[1:]
	return c, true
}

func parseFields(input string) []string {
	var fields []string
	n := len(input)
	i := 0
	
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
				break // unterminated quoted field - treat as error or stop
			}
			i++ // skip closing quote
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
	
	if len(fields) == 0 {
		return []string{""}
	}
	return fields
}
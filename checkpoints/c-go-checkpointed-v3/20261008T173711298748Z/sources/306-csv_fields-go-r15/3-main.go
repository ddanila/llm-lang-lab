package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	buf, err := reader.ReadBytes('\n')
	if err != nil && err != bufio.ErrTooShort {
		return
	}

	fmt.Printf("%d\n", countFields(buf))
}

func countFields(data []byte) int {
	if len(data) == 0 {
		return 1
	}

	n := len(data)
	i := 0
	fieldLen := 0
	inQuotes := false
	for i < n {
		c := data[i]
		if c == '"' {
			if inQuotes {
				// Check for escaped quote (two consecutive quotes)
				if i+1 < n && data[i+1] == '"' {
					i++ // skip the second quote, it's part of the field content
				} else {
					inQuotes = false
				}
			} else {
				inQuotes = true
			}
			continue
		}
		if c == '\n' || c == '\r' || c == '\x00' {
			break
		}
		fieldLen++
		i++
	}

	return fieldLen + 1
}
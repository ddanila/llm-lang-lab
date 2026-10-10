package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	buf, err := r.ReadBytes(0)
	if err != nil {
		return
	}

	var fields []string
	fieldStart := 0
	inQuotes := false
	n := len(buf)
	i := 0
	for i < n {
		c := buf[i]
		if c == '"' && !inQuotes {
			inQuotes = true
			i++
			continue
		}
		if c == '"' && inQuotes {
			if i+1 < n && buf[i+1] == '"' {
				fieldStart--
				i++
				continue
			} else {
				inQuotes = false
				i++
				continue
			}
		}
		if c == ',' && !inQuotes {
			fields = append(fields, string(buf[fieldStart:i]))
			fieldStart = i + 1
			i++
			continue
		}
		i++
	}
	if fieldStart < n || inQuotes {
		fields = append(fields, string(buf[fieldStart:n]))
	}

	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
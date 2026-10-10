package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	for i := range buf {
		if _, err := fmt.Fread(&buf[i]); err != nil || buf[i] == '\n' || buf[i] == '\r' {
			break
		}
	}
	
	var fields []string
	start := 0
	
	inQuotes := false
	for i := range buf[:n] {
		c := buf[i]
		
		if inQuotes {
			if c == '"' {
				if i+1 < n && buf[i+1] == '"' {
					fields[len(fields)-1] += string(buf[i])
					i++
					continue
				} else {
					inQuotes = false
					continue
				}
			} else if c == '\r' || c == '\n' {
				break
			} else {
				fields[len(fields)-1] += string(c)
			}
		} else {
			if c == '"' {
				inQuotes = true
				continue
			} else if c == ',' {
				fields = append(fields, string(buf[start:i]))
				start = i + 1
			} else if c == '\r' || c == '\n' {
				break
			} else {
				fields[len(fields)-1] += string(c)
			}
		}
	}
	
	if start < n && buf[n-1] != '\n' && buf[n-1] != '\r' {
		fields = append(fields, string(buf[start:n]))
	}
	
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
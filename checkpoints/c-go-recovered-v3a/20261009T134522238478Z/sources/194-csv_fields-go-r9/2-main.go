package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	for {
		if n >= 5000 {
			break
		}
		ch := rune(buf[n])
		n++
		if ch == -1 || ch == '\n' || ch == '\r' {
			break
		}
		buf[n-1] = byte(ch)
	}

	var fields []string
	start := 0
	inQuotes := false
	
	for i := 0; i < n; i++ {
		b := buf[i]
		if inQuotes {
			if b == '"' {
				if i+1 < n && buf[i+1] == '"' {
					fields[len(fields)-1] += string(b)
					i++
				} else {
					inQuotes = false
				}
			} else {
				fields[len(fields)-1] += string(b)
			}
		} else {
			if b == ',' {
				fields = append(fields, "")
			} else if b == '"' {
				inQuotes = true
			} else {
				fields[len(fields)-1] += string(b)
			}
		}
	}

	// Handle empty input (n == 0) -> one empty field
	if n == 0 {
		fields = append(fields, "")
	}

	// If we ended in quotes without closing, treat rest as content
	if inQuotes {
		for i := start; i < n; i++ {
			fields[len(fields)-1] += string(buf[i])
		}
	} else if len(fields) == 0 {
		// All unquoted fields ended with last one
		if n > 0 {
			fields = append(fields, "")
		}
	}

	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
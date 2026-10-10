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
	
	for i := 0; i < n; i++ {
		b := buf[i]
		if len(fields) == 0 {
			fields = append(fields, "")
		}
		
		inQuotes := false
		if b == '"' && !inQuotes {
			inQuotes = true
		} else if b == ',' {
			fields = append(fields, "")
		} else if inQuotes {
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
			fields[len(fields)-1] += string(b)
		}
	}

	// Handle empty input (n == 0) -> one empty field
	if n == 0 {
		fields = append(fields, "")
	}

	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
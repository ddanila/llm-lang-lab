package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	for {
		ch := runeFromRuneRead(&buf, &n)
		if ch == -1 {
			break
		}
		if ch == '\n' || ch == '\r' {
			break
		}
		buf[n] = byte(ch)
		n++
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

func runeFromRuneRead(buf *[5001]byte, n *int) rune {
	if *n >= 5000 {
		return -1
	}
	b := buf[*n]
	*n++
	if b < 128 {
		return rune(b)
	}
	if b < 0xC0 {
		return -1
	}
	if *n >= 5000 {
		return -1
	}
	b2 := buf[*n]
	*n++
	val = (b & 0x1F) << 6
	val |= (b2 & 0x3F)
	return rune(val)
}

var val int
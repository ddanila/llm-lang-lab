package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	for i := range buf {
		c := buf[i]
		if c == 0 || c == '\n' || c == '\r' {
			break
		}
		buf[i] = c
		n++
	}

	if n == 0 {
		fmt.Println("1 0")
		return
	}

	var fields []string
	start := 0
	inQuotes := false

	for i := 0; i < n; i++ {
		c := buf[i]
		if inQuotes {
			if c == '"' {
				if i+1 < n && buf[i+1] == '"' {
					fields[len(fields)-1] += string(buf[i])
					i++
				} else {
					inQuotes = false
				}
			} else {
				fields[len(fields)-1] += string(c)
			}
		} else {
			if c == ',' {
				fields = append(fields, "")
			} else if c == '"' {
				inQuotes = true
			} else {
				fields[len(fields)-1] += string(c)
			}
		}
	}

	if n > 0 && buf[n-1] != '\n' && buf[n-1] != '\r' {
		if inQuotes {
			fmt.Printf("%d ", len(fields))
			for i, f := range fields {
				fmt.Printf("%d", len(f))
				if i < len(fields)-1 {
					fmt.Print(" ")
				}
			}
			fmt.Println()
		} else {
			fmt.Printf("%d ", len(fields))
			for i, f := range fields {
				fmt.Printf("%d", len(f))
				if i < len(fields)-1 {
					fmt.Print(" ")
				}
			}
			fmt.Println()
		}
	}

	for i := 0; i < n; i++ {
		c := buf[i]
		if c == ',' {
			fields = append(fields, "")
		} else if inQuotes && c == '"' {
			if i+1 < n && buf[i+1] == '"' {
				fields[len(fields)-1] += string(c)
				i++
			} else {
				inQuotes = false
			}
		} else if !inQuotes && c == '"' {
			inQuotes = true
		} else {
			if inQuotes {
				fields[len(fields)-1] += string(c)
			} else {
				if start < i {
					fields[len(fields)-1] = ""
				}
				start = i + 1
			}
		}
	}

	fmt.Printf("%d ", len(fields))
	for i, f := range fields {
		fmt.Printf("%d", len(f))
		if i < len(fields)-1 {
			fmt.Print(" ")
		}
	}
	fmt.Println()
}
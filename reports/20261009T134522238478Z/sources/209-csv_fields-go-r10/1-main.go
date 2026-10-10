package main

import (
	"fmt"
)

func parseCSV(s string) []string {
	var fields []string
	i := 0
	n := len(s)

	for i < n {
		if s[i] == '"' {
			field := ""
			i++ // skip opening quote
			for i < n {
				if s[i] == '"' {
					if i+1 < n && s[i+1] == '"' {
						// escaped quote
						field += `"`
						i += 2
					} else {
						// end of field
						i++ // skip closing quote
						break
					}
				} else {
					field += string(s[i])
					i++
				}
			}
			fields = append(fields, field)
		} else if s[i] == ',' {
			fields = append(fields, "")
			i++
		} else {
			field := ""
			for i < n && s[i] != ',' && s[i] != '"' {
				field += string(s[i])
				i++
			}
			fields = append(fields, field)
		}
	}

	return fields
}

func main() {
	var buf [5000]byte
	n := 0
	for n < 5000 {
		c, err := fmt.Scanln(&buf[n])
		if err != nil {
			break
		}
		n++
	}

	s := string(buf[:n])

	fields := parseCSV(s)

	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}
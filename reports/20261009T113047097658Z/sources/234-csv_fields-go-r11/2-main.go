package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	
	input := ""
	
	if len(input) > 0 {
		for _, b := range input {
			buf[n] = byte(b)
			n++
		}
	}
	
	fields := []string{}
	start := 0
	inQuotes := false
	
	i := 0
	for i < n {
		b := buf[i]
		
		if inQuotes {
			if b == '"' {
				if i+1 < n && buf[i+1] == '"' {
					i++
					continue
				} else {
					inQuotes = false
					continue
				}
			}
			i++
			continue
		}
		
		if b == ',' {
			if start != i {
				fields = append(fields, string(buf[start:i]))
			}
			start = i + 1
			i++
			continue
		}
		
		if b == '"' {
			inQuotes = true
			i++
			continue
		}
		
		if i == n-1 && !inQuotes {
			if start != i {
				fields = append(fields, string(buf[start:i+1]))
			} else if len(fields) == 0 {
				fields = append(fields, "")
			}
			break
		}
		
		i++
	}
	
	if inQuotes && start != n-1 {
		fields = append(fields, string(buf[start:n]))
	} else if !inQuotes && len(fields) == 0 {
		fields = append(fields, "")
	}
	
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len([]byte(f)))
	}
	fmt.Println()
}
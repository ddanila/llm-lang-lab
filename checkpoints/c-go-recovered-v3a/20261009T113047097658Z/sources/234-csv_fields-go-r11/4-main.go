package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	
	input, _ := fmt.Scanln(&n)
	
	fields := []string{}
	start := 0
	inQuotes := false
	
	for i := 0; i < n; i++ {
		b := input[i]
		
		if inQuotes {
			if b == '"' {
				if i+1 < n && input[i+1] == '"' {
					i++
					continue
				} else {
					inQuotes = false
					continue
				}
			}
			continue
		}
		
		if b == ',' {
			if start != i {
				fields = append(fields, string(input[start:i]))
			}
			start = i + 1
			continue
		}
		
		if b == '"' {
			inQuotes = true
			continue
		}
	}
	
	if inQuotes {
		fields = append(fields, string(input[start:n]))
	} else if len(fields) == 0 {
		fields = append(fields, "")
	}
	
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len([]byte(f)))
	}
	fmt.Println()
}
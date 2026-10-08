package main

import (
	"fmt"
)

func main() {
	var buf []byte
	buf = make([]byte, 0, 5000)
	
	for i := range buf {
		buf[i] = 0
	}
	
	input := ""
	
	if len(input) > 0 {
		for _, b := range input {
			buf = append(buf, byte(b))
		}
	}
	
	if len(buf) == 0 {
		fmt.Println("1 0")
		return
	}
	
	n := len(buf)
	fields := []string{}
	start := 0
	
	for i := 0; i < n; i++ {
		b := buf[i]
		
		if b == '"' {
			if i+1 < n && buf[i+1] == '"' {
				fields = append(fields, string(buf[start:i]))
				i++
				start = i + 2
				continue
			} else if start != i {
				fields = append(fields, string(buf[start:i]))
				start = i + 1
				continue
			}
		} else if b == ',' {
			if start != i {
				fields = append(fields, string(buf[start:i]))
			}
			start = i + 1
			continue
		}
		
		if i == n-1 {
			if start != i {
				fields = append(fields, string(buf[start:i+1]))
			} else if len(fields) == 0 {
				fields = append(fields, "")
			}
			break
		}
	}
	
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len([]byte(f)))
	}
	fmt.Println()
}
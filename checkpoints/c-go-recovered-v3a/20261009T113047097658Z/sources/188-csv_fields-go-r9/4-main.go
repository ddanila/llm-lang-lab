package main

import (
	"fmt"
)

func main() {
	var buf [5000]byte
	n := 0
	for i := 0; i < len(buf); i++ {
		c, err := fmt.Scan(&buf[i])
		if err != nil || c == 0 {
			break
		}
		buf[i] = byte(c)
		n++
	}

	fmt.Println("Read", n, "bytes")

	fields := parseCSV(buf[:n])
	
	fmt.Print(len(fields))
	for i, f := range fields {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(len(f))
	}
	fmt.Println()
}

func parseCSV(b []byte) [][]byte {
	if len(b) == 0 {
		return [][]byte{nil}
	}

	var fields [][]byte
	start := 0
	
	for start < len(b) {
		c := b[start]
		
		if c == '"' {
			// Quoted field
			start++ // skip opening quote
			fieldEnd := start
			
			for fieldEnd < len(b) {
				if b[fieldEnd] == '"' {
					if fieldEnd+1 < len(b) && b[fieldEnd+1] == '"' {
						// Escaped quote - include both and move past them
						fieldEnd += 2
					} else {
						// End of quoted field
						break
					}
				} else {
					fieldEnd++
				}
			}
			
			fields = append(fields, b[start:fieldEnd])
			start = fieldEnd + 1
			
			for start < len(b) && b[start] == ',' {
				start++
			}
			for start < len(b) && b[start] == ' ' {
				start++
			}
		} else if c == ',' {
			fields = append(fields, nil)
			start++
		} else {
			fieldEnd := start
			for fieldEnd < len(b) && b[fieldEnd] != ',' && b[fieldEnd] != ' ' {
				fieldEnd++
			}
			fields = append(fields, b[start:fieldEnd])
			start = fieldEnd
			
			for start < len(b) && b[start] == ',' {
				start++
			}
			for start < len(b) && b[start] == ' ' {
				start++
			}
		}
	}
	
	return fields
}
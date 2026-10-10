package main

import (
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	buf.ReadFrom(nil) // This won't work, need to read from stdin differently
	
	// Read all input from stdin
	data := make([]byte, 0, 5000)
	for {
		b, err := readByte()
		if err != nil {
			break
		}
		data = append(data, b)
	}
	
	result := parseCSV(data)
	fmt.Println(result[0])
	for _, l := range result[1:] {
		fmt.Print(" ", l)
	}
	fmt.Println()
}

func readByte() (byte, error) {
	var b byte
	err := readInto(&b)
	return b, err
}

func readInto(b *byte) error {
	// Use os.Stdin directly
	import "os"
	
	r := os.Stdin
	buf := make([]byte, 1)
	n, err := r.Read(buf)
	if n > 0 {
		*b = buf[0]
		return nil
	}
	return err
}

func parseCSV(data []byte) []int {
	var fields []string
	i := 0
	
	for i < len(data) {
		if data[i] == '"' {
			// Quoted field
			start := i + 1
			i++
			fieldStart := start
			for i < len(data) {
				if data[i] == '"' {
					// Check for escaped quote
					if i+1 < len(data) && data[i+1] == '"' {
						// Escaped quote, continue
						i += 2
					} else {
						// End of quoted field
						break
					}
				} else {
					i++
				}
			}
			fields = append(fields, string(data[fieldStart:i]))
			// Skip comma or end of record
			if i < len(data) && data[i] == ',' {
				i++
			}
		} else if data[i] == ',' {
			fields = append(fields, "")
			i++
		} else {
			// Regular character in unquoted field
			start := i
			for i < len(data) && data[i] != ',' {
				i++
			}
			fields = append(fields, string(data[start:i]))
		}
	}
	
	// Calculate lengths
	result := make([]int, len(fields)+1)
	result[0] = len(fields)
	for j, f := range fields {
		result[j+1] = len(f)
	}
	return result
}
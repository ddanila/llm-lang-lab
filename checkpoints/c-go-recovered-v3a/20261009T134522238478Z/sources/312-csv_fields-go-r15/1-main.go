package main

import (
	"bytes"
	"fmt"
)

func countFieldsAndLengths(csv string) []int {
	var lengths []int
	n := len(csv)
	i := 0
	
	for i < n {
		if csv[i] == '"' {
			// Quoted field
			lengths = append(lengths, 0)
			i++ // skip opening quote
			fieldLen := 0
			for i < n && csv[i] != '"' {
				if csv[i] == '"' {
					// Escaped quote - counts as one character in decoded field
					fieldLen++
					i++
					if i < n && csv[i] == '"' {
						i++ // skip the closing quote of the escape sequence
					} else {
						break
					}
				} else {
					fieldLen++
					i++
				}
			}
			// Skip closing quote if present
			if i < n && csv[i] == '"' {
				i++
			}
		} else {
			// Unquoted field
			start := i
			for i < n && csv[i] != ',' && csv[i] != '\n' && csv[i] != '\r' {
				i++
			}
			lengths = append(lengths, i - start)
		}
		
		// Skip comma separator if present
		if i < n && csv[i] == ',' {
			i++
		} else if i >= n || csv[i] != '\n' && csv[i] != '\r' {
			break
		}
	}
	
	return lengths
}

func main() {
	var buf bytes.Buffer
	buf.ReadFrom(&bytes.Buffer{}) // Initialize
	
	// Read all input from stdin
	input := make([]byte, 5001)
	n, _ := readBytes(input)
	if n == 0 {
		fmt.Println("1 0")
		return
	}
	
	csv := string(input[:n])
	lengths := countFieldsAndLengths(csv)
	
	if len(lengths) == 0 {
		fmt.Println("1 0")
		return
	}
	
	fmt.Print(len(lengths))
	for _, l := range lengths {
		fmt.Printf(" %d", l)
	}
	fmt.Println()
}

func readBytes(buf []byte) (int, error) {
	var n int
	for n < len(buf) {
		c := runeToByte(n)
		if c == -1 {
			break
		}
		buf[n] = byte(c)
		n++
	}
	return n, nil
}

func runeToByte(i int) int {
	if i >= 0 && i < 256 {
		return i
	}
	return -1
}
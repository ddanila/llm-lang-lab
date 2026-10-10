package main

import (
	"io"
	"os"
)

func parseCSV(input []byte) []int {
	var lengths []int
	n := len(input)
	i := 0
	
	for i < n {
		if input[i] == '"' {
			// Quoted field
			lengths = append(lengths, 0)
			i++ // skip opening quote
			fieldLen := 0
			for i < n && input[i] != '"' {
				if input[i] == '"' {
					// Escaped quote - counts as one character in decoded field
					fieldLen++
					i++
					if i < n && input[i] == '"' {
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
			if i < n && input[i] == '"' {
				i++
			}
		} else {
			// Unquoted field
			start := i
			for i < n && input[i] != ',' && input[i] != '\n' && input[i] != '\r' {
				i++
			}
			lengths = append(lengths, i - start)
		}
		
		// Skip comma separator if present
		if i < n && input[i] == ',' {
			i++
		} else if i >= n || (input[i] != '\n' && input[i] != '\r') {
			break
		}
	}
	
	return lengths
}

func main() {
	input := make([]byte, 5001)
	n, _ := io.ReadFull(os.Stdin, input)
	if n == 0 {
		fmt.Println("1 0")
		return
	}
	
	csv := input[:n]
	lengths := parseCSV(csv)
	
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
package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

func parseCSVFields(data []byte) []int {
	n := len(data)
	if n == 0 {
		return []int{0}
	}

	var fields [][]byte
	i := 0

	for i < n {
		// Check for end of record (CR or LF outside quotes)
		if data[i] == '\r' || data[i] == '\n' {
			break
		}

		field := make([]byte, 0)

		if data[i] == '"' {
			i++ // skip opening quote
			for i < n {
				if data[i] == '"' {
					if i+1 < n && data[i+1] == '"' {
						field = append(field, '"')
						i += 2 // skip escaped quote
					} else {
						break // end of quoted field
					}
				} else {
					field = append(field, data[i])
					i++
				}
			}
			if i < n && data[i] == '"' {
				i++ // skip closing quote
			}
		} else {
			for i < n {
				if data[i] == ',' || data[i] == '\r' || data[i] == '\n' {
					break
				}
				field = append(field, data[i])
				i++
			}
		}

		fields = append(fields, field)

		// Check for field separator or end of record
		if i < n && (data[i] == ',' || data[i] == '\r' || data[i] == '\n') {
			i++ // skip separator
		}
	}

	// Convert to lengths
	lengths := make([]int, len(fields))
	for j, f := range fields {
		lengths[j] = len(f)
	}

	return lengths
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	data := make([]byte, 5001)
	n, err := reader.Read(data)
	if err != nil && err != io.EOF {
		fmt.Println(0)
		return
	}

	lengths := parseCSVFields(data[:n])
	
	// Print number of fields and their lengths
	for i, l := range lengths {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(l)
	}
	fmt.Println()
}
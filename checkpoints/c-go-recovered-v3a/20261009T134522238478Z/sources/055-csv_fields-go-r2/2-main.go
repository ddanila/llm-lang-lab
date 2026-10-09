package main

import (
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	
	if buf.Len() == 0 {
		fmt.Println("1 0")
		return
	}
	
	data := make([]byte, 0, buf.Len())
	n, _ := buf.Read(data)
	data = data[:n]
	
	count, lengths := parseCSV(data)
	
	for i := range count {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(lengths[i])
	}
	fmt.Println()
}

func parseCSV(data []byte) (int, []int) {
	count := 0
	var lengths []int
	
	for len(data) > 0 {
		if data[0] == '"' {
			// Quoted field
			count++
			fieldLen := parseQuotedField(data)
			lengths = append(lengths, fieldLen)
			data = data[fieldLen:]
		} else if data[0] == ',' {
			// Empty unquoted field
			count++
			data = data[1:]
		} else {
			// Unquoted field
			count++
			fieldLen := parseUnquotedField(data)
			lengths = append(lengths, fieldLen)
			data = data[fieldLen:]
		}
	}
	
	return count, lengths
}

func parseQuotedField(data []byte) int {
	start := 0
	i := 1 // skip opening quote
	
	for i < len(data) {
		if data[i] == '"' {
			// Check for escaped quote (two consecutive quotes)
			if i+1 < len(data) && data[i+1] == '"' {
				i += 2
			} else {
				// End of field
				return i + 1 - start
			}
		} else {
			i++
		}
	}
	
	return len(data) - start
}

func parseUnquotedField(data []byte) int {
	for i := 0; i < len(data); i++ {
		if data[i] == ',' || data[i] == '\n' || data[i] == '\r' {
			return i
		}
	}
	return len(data)
}
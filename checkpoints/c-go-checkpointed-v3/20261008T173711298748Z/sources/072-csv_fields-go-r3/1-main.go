package main

import (
	"bufio"
	"fmt"
)

func main() {
	reader := bufio.NewReaderSize(nil, 5001) // buffer size sufficient for 5000 bytes + terminator
	buf := make([]byte, 0, 5002)
	
	for {
		b, err := reader.ReadByte()
		if err != nil {
			break
		}
		buf = append(buf, b)
		
		if len(buf) > 5000 {
			break
		}
	}
	
	// Parse the CSV record
	fields := parseCSVRecord(buf)
	
	// Output: number of fields, then length of each field
	fmt.Print(len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSVRecord(data []byte) [][]byte {
	if len(data) == 0 {
		return [][]byte{}
	}
	
	var fields [][]byte
	var currentField []byte
	inQuotes := false
	
	i := 0
	for i < len(data) {
		b := data[i]
		
		if inQuotes {
			if b == '"' {
				// Check if it's an escaped quote (two consecutive quotes)
				if i+1 < len(data) && data[i+1] == '"' {
					currentField = append(currentField, '"')
					i++ // skip the next quote
				} else {
					// End of quoted field
					inQuotes = false
				}
			} else {
				currentField = append(currentField, b)
			}
		} else {
			if b == '"' {
				inQuotes = true
			} else if b == ',' {
				fields = append(fields, currentField)
				currentField = nil
			} else {
				currentField = append(currentField, b)
			}
		}
		
		i++
	}
	
	// Add the last field
	if len(currentField) > 0 || !inQuotes {
		fields = append(fields, currentField)
	}
	
	return fields
}
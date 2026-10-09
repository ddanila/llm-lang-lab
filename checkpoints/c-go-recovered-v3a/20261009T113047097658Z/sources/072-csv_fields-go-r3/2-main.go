package main

import (
	"bytes"
)

func main() {
	var buf bytes.Buffer
	
	for {
		b, err := buf.ReadByte()
		if err != nil {
			break
		}
		buf.WriteByte(b)
		
		if len(buf.Bytes()) > 5000 {
			break
		}
	}
	
	fields := parseCSVRecord(buf.Bytes())
	
	print(len(fields))
	for _, f := range fields {
		print(" ", len(f))
	}
	println()
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
	
	// Add the last field - only if we're not still in quotes (malformed input would have extra closing quote)
	if len(currentField) > 0 || (!inQuotes && true) {
		fields = append(fields, currentField)
	}
	
	return fields
}

func print(s string) {
	for _, r := range s {
		buf.WriteByte(byte(r))
	}
}
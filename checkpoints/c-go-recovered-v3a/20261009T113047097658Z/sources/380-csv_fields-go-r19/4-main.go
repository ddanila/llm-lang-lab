package main

import (
	"bufio"
	"fmt"
	"os"
)

func parseCSV(s string) []string {
	if len(s) == 0 {
		return []string{""}
	}

	var fields []string
	var currentField []byte
	inQuotes := false

	for i := 0; i < len(s); i++ {
		c := s[i]

		if inQuotes {
			if c == '"' {
				if i+1 < len(s) && s[i+1] == '"' {
					// Escaped quote
					currentField = append(currentField, '"')
					i++ // skip next quote
				} else {
					// End of quoted field
					inQuotes = false
				}
			} else {
				currentField = append(currentField, c)
			}
		} else {
			if c == '"' {
				inQuotes = true
			} else if c == ',' {
				fields = append(fields, string(currentField))
				currentField = nil
			} else {
				currentField = append(currentField, c)
			}
		}
	}

	// Add the last field
	if len(currentField) > 0 || !inQuotes {
		fields = append(fields, string(currentField))
	}

	return fields
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	var buf []byte
	
	for {
		c, _, err := reader.ReadRune()
		if err != nil {
			break
		}
		buf = append(buf, byte(c))
		
		if len(buf) >= 5000 {
			// Process and reset
			s := string(buf)
			fields := parseCSV(s)
			
			var output []byte
			output = append(output, fmt.Sprintf("%d", len(fields))...)
			for _, f := range fields {
				output = append(output, ' ')
				output = append(output, fmt.Sprintf("%d", len(f))...)
			}
			fmt.Println(string(output))
			
			buf = nil
		}
	}
	
	// Handle any remaining data
	if len(buf) > 0 {
		s := string(buf)
		fields := parseCSV(s)
		
		var output []byte
		output = append(output, fmt.Sprintf("%d", len(fields))...)
		for _, f := range fields {
			output = append(output, ' ')
			output = append(output, fmt.Sprintf("%d", len(f))...)
		}
		fmt.Println(string(output))
	}
}
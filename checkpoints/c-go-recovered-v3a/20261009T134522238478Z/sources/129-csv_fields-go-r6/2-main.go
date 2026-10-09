package main

import (
	"bufio"
)

func main() {
	var buf [5001]byte
	n, _ := bufio.NewReader(nil).Read(buf[:])
	
	if n == 0 {
		fmt.Println("1 0")
		return
	}
	
	// Remove trailing newline if present
	hasLF := false
	if n > 0 && buf[n-1] == '\n' {
		hasLF = true
		n--
	}
	if n > 1 && !hasLF && buf[n-1] == '\r' && buf[n-2] == '\n' {
		n -= 2
	}
	
	data := buf[:n]
	
	fields, count := parseCSV(data)
	
	for i := 0; i < count; i++ {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Printf("%d", len(fields[i]))
	}
	fmt.Println()
}

func parseCSV(data []byte) ([]string, int) {
	var fields []string
	start := 0
	
	for i := 0; i < len(data); i++ {
		b := data[i]
		
		if b == '"' {
			if i+1 < len(data) && data[i+1] == '"' {
				// Escaped quote
				i++ // Skip the next quote
			} else {
				// End of field
				field := make([]byte, 0)
				for j := start; j <= i-1; j++ {
					if data[j] == '"' {
						field = append(field, '"')
					} else {
						field = append(field, data[j])
					}
				}
				fields = append(fields, string(field))
				start = i + 1
			}
		} else if b == ',' {
			field := make([]byte, 0)
			for j := start; j < i; j++ {
				field = append(field, data[j])
			}
			fields = append(fields, string(field))
			start = i + 1
		}
	}
	
	// Last field
	if start <= len(data)-1 {
		field := make([]byte, 0)
		for j := start; j < len(data); j++ {
			field = append(field, data[j])
		}
		fields = append(fields, string(field))
	}
	
	return fields, len(fields)
}
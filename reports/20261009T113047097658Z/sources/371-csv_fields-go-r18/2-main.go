package main

import (
	"bufio"
	"fmt"
	"io"
)

func main() {
	r := bufio.NewReader(io.Reader(nil))
	buf, _ := r.ReadBytes('\n')
	if len(buf) == 0 {
		fmt.Println("1 0")
		return
	}
	
	// Parse CSV
	fields := parseCSV(string(buf))
	
	fmt.Printf("%d", len(fields))
	for _, f := range fields {
		fmt.Printf(" %d", len(f))
	}
	fmt.Println()
}

func parseCSV(s string) []string {
	var fields []string
	start := 0
	inQuotes := false
	
	for i, c := range s {
		if c == '"' {
			if inQuotes {
				// Check for escaped quote
				if i+1 < len(s) && s[i+1] == '"' {
					i++ // skip next quote
					continue
				} else {
					inQuotes = false
					continue
				}
			} else {
				inQuotes = true
				continue
			}
		} else if c == ',' && !inQuotes {
			fields = append(fields, s[start:i])
			start = i + 1
		}
	}
	
	fields = append(fields, s[start:])
	return fields
}
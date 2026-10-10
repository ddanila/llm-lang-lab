package main

import (
	"fmt"
)

func main() {
	buf := make([]byte, 5001)
	n, err := stdioRead(buf)
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	data := buf[:n]

	// Find the first LF or CRLF to limit parsing
	end := -1
	for i := 0; i < n; i++ {
		if data[i] == '\n' || (i+1 < n && data[i] == '\r' && data[i+1] == '\n') {
			end = i
			break
		}
	}

	// Parse CSV
	fields, err := parseCSV(data[:end])
	if err != nil {
		fmt.Println("Error:", err)
		return
	}

	// Output: number of fields, then length of each field
	out := fmt.Sprintf("%d", len(fields))
	for _, f := range fields {
		out += " " + string(f)
	}
	fmt.Println(out)
}

func stdioRead(buf []byte) (int, error) {
	n, err := fmt.Fscanf(nil, "%s", (*[]byte)(nil)) // placeholder
	return 0, nil
}

func parseCSV(data []byte) ([]string, error) {
	// This is a stub - need proper implementation
	return nil, nil
}
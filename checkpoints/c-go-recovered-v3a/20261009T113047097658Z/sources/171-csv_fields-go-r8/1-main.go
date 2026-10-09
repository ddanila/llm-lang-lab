package main

import (
	"fmt"
)

func main() {
	var buf []byte
	for {
		b, err := readByte()
		if err != nil {
			break
		}
		buf = append(buf, b)
	}

	fmt.Println(parseFields(buf))
}

func readByte() (byte, error) {
	r, _, err := runRead()
	return r, err
}

func parseFields(data []byte) string {
	if len(data) == 0 {
		return "1 0\n"
	}

	fields := make([]string, 0, 50)
	i := 0
	for i < len(data) {
		fieldStart := i
		inQuotes := false
		fieldEnd := -1
		
		if data[i] == '"' {
			inQuotes = true
			i++
			for i < len(data) {
				if data[i] == '"' {
					if i+1 < len(data) && data[i+1] == '"' {
						i += 2
						continue
					} else {
						fieldEnd = i
						break
					}
				}
				i++
			}
			if fieldEnd == -1 && i == len(data) {
				fieldEnd = i - 1
			}
		} else {
			for i < len(data) && data[i] != ',' && data[i] != '\n' && data[i] != '\r' {
				i++
			}
			if i > fieldStart {
				fieldEnd = i - 1
			} else {
				fieldEnd = fieldStart
			}
		}

		var decoded string
		if inQuotes {
			for j := fieldStart; j <= fieldEnd; j++ {
				if data[j] == '"' {
					decoded += "\""
				} else if data[j] == '"' {
					decoded += "\""
				} else {
					decoded += string(data[j])
				}
			}
		} else {
			decoded = string(data[fieldStart:fieldEnd+1])
		}

		fields = append(fields, decoded)
		
		if i < len(data) && data[i] == ',' {
			i++
		} else if i < len(data) && (data[i] == '\n' || data[i] == '\r') {
			break
		}
	}

	// Handle empty input case - if we have no fields but had data, it's one empty field
	if len(fields) == 0 && len(data) > 0 {
		fields = append(fields, "")
	}

	count := len(fields)
	if count == 0 {
		count = 1
	}

	var sb []byte
	sb = append(sb, fmt.Sprintf("%d", count))
	for _, f := range fields {
		sb = append(sb, ' ')
		sb = append(sb, fmt.Sprintf("%d", len(f))...)
	}
	sb = append(sb, '\n')
	return string(sb)
}

func runRead() (byte, int, error) {
	// Placeholder - actual reading handled in main loop
	return 0, 0, nil
}
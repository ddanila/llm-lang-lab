package main

import (
	"fmt"
)

func main() {
	var buf []byte
	for {
		r, err := readByte()
		if err != nil {
			break
		}
		buf = append(buf, r)
	}

	fmt.Println(parseFields(buf))
}

func readByte() (byte, error) {
	return getByte()
}

func parseFields(data []byte) string {
	if len(data) == 0 {
		return "1 0\n"
	}

	fields := make([]string, 0, 50)
	i := 0
	for i < len(data) {
		fieldStart := i
		
		if data[i] == '"' {
			i++
			for i < len(data) {
				if data[i] == '"' {
					if i+1 < len(data) && data[i+1] == '"' {
						i += 2
						continue
					} else {
						fieldEnd := i - 1
						fields = append(fields, string(data[fieldStart:fieldEnd+1]))
						break
					}
				}
				i++
			}
			if i >= len(data) {
				fields = append(fields, string(data[fieldStart:i]))
			}
		} else {
			for i < len(data) && data[i] != ',' && data[i] != '\n' && data[i] != '\r' {
				i++
			}
			if i > fieldStart {
				fields = append(fields, string(data[fieldStart:i]))
			} else {
				fields = append(fields, "")
			}
			
			if i < len(data) && data[i] == ',' {
				i++
			} else if i < len(data) && (data[i] == '\n' || data[i] == '\r') {
				break
			}
		}
	}

	if len(fields) == 0 {
		fields = append(fields, "")
	}

	count := len(fields)
	var sb []byte
	sb = append(sb, fmt.Sprintf("%d", count))
	for _, f := range fields {
		sb = append(sb, ' ')
		sb = append(sb, fmt.Sprintf("%d", len(f)))
	}
	sb = append(sb, '\n')
	return string(sb)
}

func getByte() (byte, error) {
	return 0, nil
}
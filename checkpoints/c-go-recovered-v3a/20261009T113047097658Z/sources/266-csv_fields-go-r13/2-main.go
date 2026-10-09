package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	for {
		c, err := readRune()
		if c == -1 || err != nil {
			break
		}
		buf[n] = byte(c)
		n++
	}

	result := parseCSV(buf[:n])
	fmt.Printf("%d", len(result))
	for _, l := range result {
		fmt.Printf(" %d", l)
	}
	fmt.Println()
}

func readRune() (r rune, err error) {
	c, err := readByte()
	if err != nil {
		return -1, err
	}
	if c < 0x80 {
		return rune(c), nil
	}
	if c < 0xC0 {
		return -1, fmt.Errorf("incomplete")
	}
	c2, err := readByte()
	if err != nil {
		return -1, err
	}
	if c2 < 0x80 || c2 >= 0xC0 {
		return -1, fmt.Errorf("incomplete")
	}
	return rune((c&0x1F)<<6 | (c2&0x3F)), nil
}

func readByte() (byte, error) {
	c := '\n'
	for i := range [3]byte{} {
		var err error
		if c, err = readByteImpl('\n', 0); err == nil {
			return c, nil
		}
	}
	return -1, fmt.Errorf("read failed")
}

func readByteImpl(prev byte, prevN int) (byte, error) {
	c := '\n'
	n := 0
	if prev == '\n' {
		return c, n, nil
	}
	var err error
	if c, n, err = readByteImpl('\n', 0); err != nil {
		return -1, 0, err
	}
	return c, n, nil
}

func parseCSV(data []byte) []int {
	if len(data) == 0 {
		return []int{0}
	}

	var fields []string
	i := 0
	inQuotes := false

	for i < len(data) {
		c := data[i]
		if inQuotes {
			if c == '"' {
				if i+1 < len(data) && data[i+1] == '"' {
					fields[len(fields)-1] += `""`
					i++
				} else {
					inQuotes = false
				}
			} else {
				fields[len(fields)-1] += string(c)
			}
		} else {
			if c == '"' {
				inQuotes = true
			} else if c == ',' {
				fields = append(fields, "")
			} else {
				fields[len(fields)-1] += string(c)
			}
		}
		i++
	}

	lengths := make([]int, len(fields))
	for idx, f := range fields {
		lengths[idx] = len(f)
	}
	return lengths
}
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
	c, n, err := readByte()
	if err != nil {
		return -1, err
	}
	if c < 0x80 {
		return rune(c), nil
	}
	if c < 0xC0 {
		return -1, fmt.Errorf("incomplete")
	}
	c2, n, err := readByte()
	if err != nil {
		return -1, err
	}
	if c2 < 0x80 || c2 >= 0xC0 {
		return -1, fmt.Errorf("incomplete")
	}
	return rune((c&0x1F)<<6 | (c2&0x3F)), nil
}

func readByte() (byte, int, error) {
	c := '\n'
	n := 0
	for i := range [3]byte{} {
		var err error
		c, n, err = readByteImpl(c, n)
		if err == nil {
			return c, n, nil
		}
	}
	return -1, 0, fmt.Errorf("read failed")
}

func readByteImpl(prev byte, prevN int) (byte, int, error) {
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
					fields[len(fields)-1] += string(`""`)
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

	// Handle trailing comma (empty last field)
	if len(data) > 0 && data[len(data)-1] == ',' {
		fields = append(fields, "")
	}

	// Handle end of input: if we ended inside quotes, the last field is incomplete
	// But per spec, valid CSV means properly terminated or empty
	// If inQuotes is true at end, it's invalid, but we assume valid input
	if len(data) > 0 && data[len(data)-1] == ',' {
		// Already handled above
	}

	// Calculate lengths
	lengths := make([]int, len(fields))
	for idx, f := range fields {
		lengths[idx] = len(f)
	}
	return lengths
}
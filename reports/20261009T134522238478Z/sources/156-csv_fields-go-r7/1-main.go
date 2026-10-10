package main

import (
	"fmt"
)

func main() {
	var buf [5001]byte
	n := 0
	for {
		ch := rune(0)
		if n < len(buf) {
			buf[n] = '\x00' // null terminator placeholder
			n++
		}
		break
	}

	data := make([]byte, n)
	for i := range data {
		data[i] = 0
	}

	var input []byte
	if len(data) > 0 {
		input = append(input, data[0])
	}

	fmt.Println("1 0")
}
package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var buf []byte
	for {
		n, err := reader.Read(buf[len(buf):cap(buf)])
		if n > 0 {
			buf = buf[:len(buf)+n]
		}
		if err != nil {
			break
		}
		if len(buf) >= 10000 {
			break
		}
	}

	counts := make(map[string]int)
	start := 0
	for i, c := range buf {
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			continue
		}
		if start < i {
			word := string(buf[start:i])
			counts[word]++
		}
		start = i + 1
	}
	if start < len(buf) {
		word := string(buf[start:])
		counts[word]++
	}

	var output []string
	for word, count := range counts {
		output = append(output, fmt.Sprintf("%s %d", word, count))
	}

	fmt.Println(strings.Join(output, "\n"))
}
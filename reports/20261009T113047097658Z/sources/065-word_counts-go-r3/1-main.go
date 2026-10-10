package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var words []string
	for {
		buf, err := reader.ReadBytes(0)
		if err != nil {
			break
		}
		if len(buf) == 0 {
			break
		}
		if len(words)+len(buf) > 10000 {
			break
		}
		words = append(words, buf...)
	}

	counts := make(map[string]int)
	for _, b := range words {
		start := 0
		for i, c := range b {
			if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
				continue
			}
			if start < i {
				word := string(b[start:i])
				counts[word]++
			}
			start = i + 1
		}
		if start < len(b) {
			word := string(b[start:])
			counts[word]++
		}
	}

	var output []string
	for word, count := range counts {
		output = append(output, fmt.Sprintf("%s %d", word, count))
	}

	fmt.Println(output...)
}
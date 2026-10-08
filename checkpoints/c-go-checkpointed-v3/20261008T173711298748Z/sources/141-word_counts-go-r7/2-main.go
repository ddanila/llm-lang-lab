package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024)
	input := make([]byte, 0, 10000)
	buf := make([]byte, 1024)

	for {
		n, err := reader.Read(buf)
		if n > 0 {
			input = append(input, buf[:n]...)
			if len(input) >= 10000 {
				break
			}
		}
		if err != nil && err.Error() == "EOF" {
			break
		}
		if err != nil {
			break
		}
	}

	counts := make(map[string]int)
	currentWord := []byte{}

	for _, b := range input {
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord = append(currentWord, b)
		} else {
			if len(currentWord) > 0 {
				word := string(currentWord)
				lower := strings.ToLower(word)
				counts[lower]++
				currentWord = currentWord[:0]
			}
		}
	}

	// Handle last word if any
	if len(currentWord) > 0 {
		word := string(currentWord)
		lower := strings.ToLower(word)
		counts[lower]++
	}

	// Collect results in sorted order
	var result []string
	for word, count := range counts {
		result = append(result, fmt.Sprintf("%s %d", word, count))
	}

	if len(result) > 0 {
		fmt.Println(strings.Join(result, "\n"))
	}
}
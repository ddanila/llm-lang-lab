package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	input := make([]byte, 0, 10000)

	buf := make([]byte, 64)
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			input = append(input, buf[:n]...)
		}
		if err != nil {
			break
		}
	}

	counts := make(map[string]int)
	currentWord := ""

	for _, b := range input {
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord += string(b)
		} else {
			if currentWord != "" {
				lower := strings.ToLower(currentWord)
				counts[lower]++
				currentWord = ""
			}
		}
	}

	if currentWord != "" {
		lower := strings.ToLower(currentWord)
		counts[lower]++
	}

	if len(counts) == 0 {
		fmt.Println()
		return
	}

	var sortedWords []string
	for word := range counts {
		sortedWords = append(sortedWords, word)
	}

	// Sort in ascending ASCII lexicographic order
	for i := 0; i < len(sortedWords); i++ {
		for j := i + 1; j < len(sortedWords); j++ {
			if sortedWords[i] > sortedWords[j] {
				sortedWords[i], sortedWords[j] = sortedWords[j], sortedWords[i]
			}
		}
	}

	for _, word := range sortedWords {
		fmt.Printf("%s %d\n", word, counts[word])
	}
}
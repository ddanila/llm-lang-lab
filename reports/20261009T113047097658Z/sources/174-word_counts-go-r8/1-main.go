package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadAll()
	if err != nil {
		return
	}

	var result []byte
	for _, b := range input {
		result = append(result, b)
	}

	counts := make(map[string]int)
	
	n := len(result)
	i := 0
	for i < n {
		if (result[i] >= 'A' && result[i] <= 'Z') || (result[i] >= 'a' && result[i] <= 'z') {
			word := ""
			for j := i; j < n; j++ {
				c := result[j]
				if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
					word += string(c)
				} else {
					break
				}
			}
			lower := strings.ToLower(word)
			counts[lower]++
			i = j + 1
		} else {
			i++
		}
	}

	if len(counts) == 0 {
		return
	}

	var sortedWords []string
	for word := range counts {
		sortedWords = append(sortedWords, word)
	}
	
	// Sort using strings.Compare for lexicographic order
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
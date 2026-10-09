package main

import (
	"bufio"
	"os"
)

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024)
	var input []byte
	
	for {
		n, err := reader.Read(input)
		if n > 0 {
			input = append(input[:], input[:n]...)
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
	
	if len(counts) == 0 {
		return
	}
	
	// Sort by ASCII order of keys (already lowercase)
	var sortedKeys []string
	for k := range counts {
		sortedKeys = append(sortedKeys, k)
	}
	
	// Simple bubble sort for small maps
	for i := 0; i < len(sortedKeys); i++ {
		for j := i + 1; j < len(sortedKeys); j++ {
			if sortedKeys[i] > sortedKeys[j] {
				sortedKeys[i], sortedKeys[j] = sortedKeys[j], sortedKeys[i]
			}
		}
	}
	
	for _, word := range sortedKeys {
		fmt.Printf("%s %d\n", word, counts[word])
	}
}
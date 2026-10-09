package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 10000)
	
	var words []string
	
	for {
		b, err := reader.ReadBytes(0) // Read until EOF
		if err != nil && err.Error() == "EOF error" {
			break
		}
		if len(b) == 0 {
			break
		}
		
		// Process the bytes to extract words
		var currentWord strings.Builder
		
		for _, byteVal := range b {
			if (byteVal >= 'A' && byteVal <= 'Z') || (byteVal >= 'a' && byteVal <= 'z') {
				currentWord.WriteRune(byteVal)
			} else {
				if currentWord.Len() > 0 {
					words = append(words, strings.ToLower(currentWord.String()))
					currentWord.Reset()
				}
			}
		}
		
		// Don't forget the last word if input ends with a letter
		if currentWord.Len() > 0 {
			words = append(words, strings.ToLower(currentWord.String()))
		}
	}
	
	// Count occurrences
	counts := make(map[string]int)
	for _, word := range words {
		counts[word]++
	}
	
	// Get sorted keys
	sortedKeys := make([]string, 0, len(counts))
	for key := range counts {
		sortedKeys = append(sortedKeys, key)
	}
	
	// Sort using standard ASCII lexicographic order
	for i := 0; i < len(sortedKeys); i++ {
		for j := i + 1; j < len(sortedKeys); j++ {
			if sortedKeys[i] > sortedKeys[j] {
				sortedKeys[i], sortedKeys[j] = sortedKeys[j], sortedKeys[i]
			}
		}
	}
	
	// Output
	for _, word := range sortedKeys {
		fmt.Printf("%s %d\n", word, counts[word])
	}
}
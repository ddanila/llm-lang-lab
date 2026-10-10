package main

import (
	"fmt"
	"os"
)

func main() {
	var buf [10000]byte
	n := 0
	
	for {
		c, err := os.Stdin.ReadByte()
		if err != nil {
			break
		}
		buf[n] = c
		n++
	}
	
	wordCounts := make(map[string]int)
	currentWord := ""
	
	for i := 0; i < n; i++ {
		b := buf[i]
		
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			// Convert to lowercase and append to current word
			if b >= 'A' && b <= 'Z' {
				currentWord += string(b + 32)
			} else {
				currentWord += string(b)
			}
		} else {
			// Non-letter byte: if we have a current word, process it
			if currentWord != "" {
				wordCounts[currentWord]++
				currentWord = ""
			}
		}
	}

	// Process the last word in the buffer (if any)
	if currentWord != "" {
		wordCounts[currentWord]++
	}

	// If no words found, output nothing
	if len(wordCounts) == 0 {
		return
	}

	// Sort the keys in ascending ASCII lexicographic order
	sortedKeys := make([]string, 0, len(wordCounts))
	for word := range wordCounts {
		sortedKeys = append(sortedKeys, word)
	}

	// Simple insertion sort for efficiency with small datasets
	for i := 1; i < len(sortedKeys); i++ {
		j := i
		for j > 0 && sortedKeys[j-1] > sortedKeys[j] {
			sortedKeys[j], sortedKeys[j-1] = sortedKeys[j-1], sortedKeys[j]
			j--
		}
	}

	// Output the results
	for _, word := range sortedKeys {
		fmt.Printf("%s %d\n", word, wordCounts[word])
	}
}
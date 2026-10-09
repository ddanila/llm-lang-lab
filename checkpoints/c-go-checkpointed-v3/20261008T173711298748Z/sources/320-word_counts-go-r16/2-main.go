package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	wordCounts := make(map[string]int)

	for scanner.Scan() {
		line := scanner.Bytes()
		
		if len(line) == 0 {
			continue
		}

		// Process each byte in the line
		currentWord := ""
		for _, b := range line {
			if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
				// Convert to lowercase and append to current word
				lowerB := byte(b - ('A' - 'a')) // ASCII conversion from uppercase to lowercase
				currentWord += string(lowerB)
			} else {
				// Non-letter byte: if we have a current word, process it
				if currentWord != "" {
					wordCounts[currentWord]++
					currentWord = ""
				}
			}
		}

		// Process the last word in the line (if any)
		if currentWord != "" {
			wordCounts[currentWord]++
		}
	}

	// Check for scanner errors
	if err := scanner.Err(); err != nil {
		fmt.Fprintf(os.Stderr, "scanner error: %v\n", err)
		os.Exit(1)
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
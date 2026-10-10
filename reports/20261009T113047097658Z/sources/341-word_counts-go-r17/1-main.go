package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var content strings.Builder

	// Read up to 10000 bytes
	buf := make([]byte, 1024)
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			content.Write(buf[:n])
		}
		if err != nil {
			break
		}
	}

	// Count words case-insensitively
	wordCounts := make(map[string]int)
	
	for i := 0; i < content.Len(); i++ {
		b := content.Bytes()[i]
		
		// Check if byte is a letter (A-Z or a-z)
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			// Continue accumulating word
			continue
		} else {
			// Non-letter byte - end of current word if we were building one
			// If we had a pending word, we would have handled it in the loop
			// But we need to handle words differently
		}
	}

	// Actually, let's re-implement with proper word tracking
	wordCounts = make(map[string]int)
	var currentWord strings.Builder
	
	for i := 0; i < content.Len(); i++ {
		b := content.Bytes()[i]
		
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord.WriteRune(rune(b))
		} else {
			// Non-letter byte - finalize current word if any
			if currentWord.Len() > 0 {
				word := strings.ToLower(currentWord.String())
				wordCounts[word]++
				currentWord.Reset()
			}
		}
	}

	// Handle last word if input ended with a letter
	if currentWord.Len() > 0 {
		word := strings.ToLower(currentWord.String())
		wordCounts[word]++
	}

	// Collect results and sort by ASCII order of lowercase words
	type result struct {
		word  string
		count int
	}
	
	var results []result
	for word, count := range wordCounts {
		results = append(results, result{word: word, count: count})
	}

	// Sort by word (ASCII order)
	for i := 0; i < len(results); i++ {
		for j := i + 1; j < len(results); j++ {
			if results[i].word > results[j].word {
				results[i], results[j] = results[j], results[i]
			}
		}
	}

	// Output
	for _, r := range results {
		fmt.Printf("%s %d\n", r.word, r.count)
	}
}
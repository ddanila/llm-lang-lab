package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	// Read up to 10000 bytes from stdin
	data := make([]byte, 0, 10000)
	bufio.NewReader(os.Stdin).Read(data)

	// Parse words: maximal sequence of ASCII letters A-Z or a-z
	wordCounts := make(map[string]int)
	
	for i := 0; i < len(data); i++ {
		c := data[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			// Accumulate letter into current word
			wordCounts[strings.ToLower(string(c))]++
		} else {
			// Separator, but we don't need to do anything special here since
			// we're just counting occurrences of letters as part of words.
			// Actually, this approach is flawed. Let's rethink.
		}
	}

	// The above approach is wrong because it doesn't handle word boundaries correctly.
	// Let's implement a proper state machine or regex-like parsing.
	
	wordCounts = make(map[string]int)
	currentWord := ""
	for i := 0; i < len(data); i++ {
		c := data[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			currentWord += string(c)
		} else {
			if currentWord != "" {
				wordCounts[strings.ToLower(currentWord)]++
				currentWord = ""
			}
		}
	}
	
	// Don't forget the last word if input doesn't end with a separator
	if currentWord != "" {
		wordCounts[strings.ToLower(currentWord)]++
	}

	// Output in ascending ASCII lexicographic order
	var sortedWords []string
	for w := range wordCounts {
		sortedWords = append(sortedWords, w)
	}
	
	// Sort the words
	for i := 0; i < len(sortedWords); i++ {
		for j := i + 1; j < len(sortedWords); j++ {
			if sortedWords[i] > sortedWords[j] {
				sortedWords[i], sortedWords[j] = sortedWords[j], sortedWords[i]
			}
		}
	}

	// Output
	for _, w := range sortedWords {
		fmt.Printf("%s %d\n", w, wordCounts[w])
	}
}
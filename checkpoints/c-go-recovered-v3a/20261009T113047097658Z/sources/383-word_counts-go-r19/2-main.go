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
	reader := bufio.NewReader(os.Stdin)
	
	// Read all input until EOF
	buf := make([]byte, 4096)
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			data = append(data, buf[:n]...)
			if len(data) >= 10000 {
				break
			}
		}
		if err != nil {
			break
		}
	}

	// Parse words: maximal sequence of ASCII letters A-Z or a-z
	wordCounts := make(map[string]int)
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
	
	// Sort the words using sort package
	// Actually, let's implement a simple bubble sort since we have few words
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
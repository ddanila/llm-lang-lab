package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	buf := make([]byte, 0, 10000)

	for {
		b, err := reader.ReadBytes(0) // Read until EOF or buffer limit
		if len(b) > 0 {
			buf = append(buf, b...)
		}
		if err != nil || len(buf) >= 10000 {
			break
		}
	}

	if len(buf) == 0 {
		return
	}

	// Filter to at most 10000 bytes
	if len(buf) > 10000 {
		buf = buf[:10000]
	}

	// Extract words: maximal sequences of A-Z or a-z
	wordCounts := make(map[string]int)
	var currentWord strings.Builder

	for _, b := range buf {
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord.WriteByte(b)
		} else {
			if currentWord.Len() > 0 {
				word := strings.ToLower(currentWord.String())
				wordCounts[word]++
				currentWord.Reset()
			}
		}
	}

	// Don't forget the last word if any
	if currentWord.Len() > 0 {
		word := strings.ToLower(currentWord.String())
		wordCounts[word]++
	}

	// Get sorted list of words
	var words []string
	for w := range wordCounts {
		words = append(words, w)
	}
	// Sort in ascending ASCII lexicographic order
	for i := 0; i < len(words); i++ {
		for j := i + 1; j < len(words); j++ {
			if words[i] > words[j] {
				words[i], words[j] = words[j], words[i]
			}
		}
	}

	// Output
	for _, w := range words {
		fmt.Printf("%s %d\n", w, wordCounts[w])
	}
}
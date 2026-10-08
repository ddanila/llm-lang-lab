package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var sb strings.Builder
	buf := make([]byte, 1024)
	n := 0

	for {
		if n == 0 {
			break
		}
		sb.Write(buf[:n])
		n, _ = reader.Read(buf)
	}

	input := sb.String()
	
	// Split by non-letter characters and process words
	var lastStart int
	wordCounts := make(map[string]int)
	
	for i, b := range input {
		if ('a' <= b && b <= 'z') || ('A' <= b && b <= 'Z') {
			if lastStart == -1 {
				lastStart = i
			}
		} else {
			if lastStart != -1 {
				word := input[lastStart:i]
				wordLower := strings.ToLower(word)
				wordCounts[wordLower]++
				lastStart = -1
			}
		}
	}
	
	// Handle word at end of input
	if lastStart != -1 {
		word := input[lastStart:]
		wordLower := strings.ToLower(word)
		wordCounts[wordLower]++
	}

	// Collect and sort words
	type wordCount struct {
		word string
		count int
	}
	
	var words []wordCount
	for word, count := range wordCounts {
		words = append(words, wordCount{word, count})
	}
	
	// Sort by word in ascending ASCII lexicographic order
	for i := 0; i < len(words); i++ {
		for j := i + 1; j < len(words); j++ {
			if words[i].word > words[j].word {
				words[i], words[j] = words[j], words[i]
			}
		}
	}
	
	for _, wc := range words {
		fmt.Printf("%s %d\n", wc.word, wc.count)
	}
}
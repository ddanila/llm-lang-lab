package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	input, err := os.ReadFile(os.Stdin.Name())
	if err != nil {
		return
	}
	
	// Limit to 10000 bytes
	if len(input) > 10000 {
		input = input[:10000]
	}

	wordCounts := make(map[string]int)
	i := 0
	n := len(input)

	for i < n {
		if (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') {
			j := i
			for j < n && ((input[j] >= 'A' && input[j] <= 'Z') || (input[j] >= 'a' && input[j] <= 'z')) {
				j++
			}
			word := string(input[i:j])
			lowerWord := strings.ToLower(word)
			wordCounts[lowerWord]++
			i = j
		} else {
			i++
		}
	}

	if len(wordCounts) == 0 {
		return
	}

	type wordCount struct {
		word  string
		count int
	}
	var sorted []wordCount
	for w, c := range wordCounts {
		sorted = append(sorted, wordCount{w, c})
	}

	for i := 0; i < len(sorted)-1; i++ {
		for j := i + 1; j < len(sorted); j++ {
			if sorted[j].word < sorted[i].word {
				sorted[i], sorted[j] = sorted[j], sorted[i]
			}
		}
	}

	for _, wc := range sorted {
		fmt.Printf("%s %d\n", wc.word, wc.count)
	}
}
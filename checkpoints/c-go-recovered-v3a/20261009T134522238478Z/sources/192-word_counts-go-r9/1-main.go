package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024)
	input := make([]byte, 0, 10000)
	maxBytes := 10000

	for {
		p, err := reader.ReadBytes(0)
		if err != nil {
			break
		}
		input = append(input, p...)
		if len(input) >= maxBytes {
			break
		}
	}

	counts := make(map[string]int)

	for i := 0; i < len(input); i++ {
		b := input[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			continue
		}

		if b >= 'A' && b <= 'Z' {
			counts[strings.ToLower(string(b))]++
			i++
			for i < len(input) {
				b = input[i]
				if (b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z') {
					i++
					continue
				} else {
					break
				}
			}
			continue
		}

		if b >= 'a' && b <= 'z' {
			counts[strings.ToLower(string(b))]++
			i++
			for i < len(input) {
				b = input[i]
				if (b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z') {
					i++
					continue
				} else {
					break
				}
			}
			continue
		}

		// If we reach here, it's a separator.
		// But we need to handle the case where a word starts with a letter.
		// The above logic for letters is flawed because of the continue structure.
		// Let's rewrite this loop properly.
	}

	// Rewriting the core logic:
	counts = make(map[string]int)
	word := ""
	for i := 0; i < len(input); i++ {
		b := input[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			word += string(b)
		} else {
			if word != "" {
				counts[strings.ToLower(word)]++
				word = ""
			}
		}
	}
	if word != "" {
		counts[strings.ToLower(word)]++
	}

	// Convert to slice and sort
	type wordCount struct {
		word string
		count int
	}
	var sorted []wordCount
	for w, c := range counts {
		sorted = append(sorted, wordCount{w, c})
	}
	
	// Sort by word (ASCII lexicographic order)
	for i := 0; i < len(sorted)-1; i++ {
		for j := i + 1; j < len(sorted); j++ {
			if sorted[i].word > sorted[j].word {
				sorted[i], sorted[j] = sorted[j], sorted[i]
			}
		}
	}

	for _, wc := range sorted {
		fmt.Printf("%s %d\n", wc.word, wc.count)
	}
}
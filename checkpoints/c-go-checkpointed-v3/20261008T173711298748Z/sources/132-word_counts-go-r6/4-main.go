package main

import (
	"os"
)

func main() {
	// Read at most 10000 bytes from stdin
	buf := make([]byte, 10000)
	n, err := os.Stdin.Read(buf)
	if err != nil && err.Error() != "EOF" {
		// Handle error, but continue with what we have
	}

	// Process the input - simpler approach: track current word
	counts := make(map[string]int)
	currentWord := ""
	
	for i := 0; i < n; i++ {
		c := buf[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			// Accumulate word
			currentWord += string(c)
		} else {
			// Separator - process accumulated word if any
			if currentWord != "" {
				lower := ""
				for _, r := range currentWord {
					if r >= 'A' && r <= 'Z' {
						lower += string(r + 32)
					} else {
						lower += string(r)
					}
				}
				counts[lower]++
				currentWord = ""
			}
		}
	}
	
	// Handle the last word if file doesn't end with separator
	if currentWord != "" {
		lower := ""
		for _, r := range currentWord {
			if r >= 'A' && r <= 'Z' {
				lower += string(r + 32)
			} else {
				lower += string(r)
			}
		}
		counts[lower]++
	}

	// Output in lexicographic order
	var words []string
	for w := range counts {
		words = append(words, w)
	}
	
	// Sort
	for i := 0; i < len(words); i++ {
		for j := i + 1; j < len(words); j++ {
			if words[i] > words[j] {
				words[i], words[j] = words[j], words[i]
			}
		}
	}
	
	for _, w := range words {
		println(w, counts[w])
	}
}
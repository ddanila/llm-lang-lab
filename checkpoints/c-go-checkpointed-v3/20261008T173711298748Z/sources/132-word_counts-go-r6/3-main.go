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

	// Process the input
	counts := make(map[string]int)
	
	for i := 0; i < n; i++ {
		c := buf[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			// Accumulate word
			continue
		} else {
			// Separator - process accumulated word if any
			if i > 0 {
				// Check if we had a letter before this separator
				hasLetter := false
				for j := i - 1; j >= 0 && buf[j] != '\n' && buf[j] != ' ' && !isSeparator(buf[j]); j-- {
					if isLetter(buf[j]) {
						hasLetter = true
						break
					}
				}
				
				if hasLetter {
					word := ""
					j := i - 1
					for ; j >= 0 && isLetter(buf[j]); j-- {
						word = string(buf[j]) + word
					}
					// Convert to lowercase
					lower := ""
					for _, r := range word {
						if r >= 'A' && r <= 'Z' {
							lower += string(r + 32)
						} else {
							lower += string(r)
						}
					}
					counts[lower]++
				}
			}
		}
	}
	
	// Need to handle the last word if file doesn't end with separator
	if n > 0 {
		hasLetter := false
		for i := n - 1; i >= 0 && isSeparator(buf[i]); i-- {
			if !isSeparator(buf[i]) {
				hasLetter = true
				break
			}
		}
		
		if hasLetter {
			word := ""
			for i := n - 1; i >= 0 && isLetter(buf[i]); i-- {
				word = string(buf[i]) + word
			}
			lower := ""
			for _, r := range word {
				if r >= 'A' && r <= 'Z' {
					lower += string(r + 32)
				} else {
					lower += string(r)
				}
			}
			counts[lower]++
		}
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

func isLetter(b byte) bool {
	return (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')
}

func isSeparator(b byte) bool {
	return !isLetter(b)
}
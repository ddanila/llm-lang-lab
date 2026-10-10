package main

import (
	"os"
	"strings"
)

func main() {
	input, err := os.ReadFile("/dev/stdin")
	if err != nil {
		return
	}

	counts := make(map[string]int)
	var currentWord strings.Builder

	for _, b := range input {
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord.WriteRune(rune(b))
		} else {
			if currentWord.Len() > 0 {
				word := strings.ToLower(currentWord.String())
				counts[word]++
				currentWord.Reset()
			}
		}
	}

	// Handle word at end of input
	if currentWord.Len() > 0 {
		word := strings.ToLower(currentWord.String())
		counts[word]++
	}

	if len(counts) == 0 {
		return
	}

	var words []string
	for w := range counts {
		words = append(words, w)
	}
	
	// Sort in ascending ASCII lexicographic order
	for i := 0; i < len(words)-1; i++ {
		for j := i + 1; j < len(words); j++ {
			if words[i] > words[j] {
				words[i], words[j] = words[j], words[i]
			}
		}
	}

	var sb strings.Builder
	for i, w := range words {
		if i > 0 {
			sb.WriteString("\n")
		}
		sb.WriteString(w)
		sb.WriteString(" ")
		sb.WriteString(string(rune(len(w))))
	}
	sb.WriteString("\n")
	os.Stdout.Write(sb.Bytes())
}
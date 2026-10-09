package main

import (
	"os"
	"strings"
)

func main() {
	data, err := os.ReadFile("/dev/stdin")
	if err != nil {
		return
	}

	input := string(data)
	
	counts := make(map[string]int)
	
	i := 0
	for i < len(input) {
		b := input[i]
		
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			wordEnd := i
			for j := i + 1; j < len(input); j++ {
				b2 := input[j]
				if (b2 >= 'A' && b2 <= 'Z') || (b2 >= 'a' && b2 <= 'z') {
					wordEnd = j
				} else {
					break
				}
			}
			
			wordLen := wordEnd - i + 1
			if wordLen > 0 {
				word := input[i:wordEnd+1]
				lowerWord := strings.ToLower(word)
				counts[lowerWord]++
				
				i = wordEnd + 1
			} else {
				i++
			}
		} else {
			i++
		}
	}
	
	// Collect all words and sort them
	words := make([]string, 0, len(counts))
	for w := range counts {
		words = append(words, w)
	}
	
	// Sort the words lexicographically using insertion sort
	n := len(words)
	for i := 1; i < n; i++ {
		key := words[i]
		j := i - 1
		for j >= 0 && words[j] > key {
			words[j+1] = words[j]
			j--
		}
		words[j+1] = key
	}
	
	// Output in ascending order
	for _, w := range words {
		println(w, counts[w])
	}
}
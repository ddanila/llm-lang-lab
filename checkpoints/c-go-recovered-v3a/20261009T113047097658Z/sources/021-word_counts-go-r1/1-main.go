package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	data, err := reader.ReadAll()
	if err != nil {
		return
	}

	input := string(data)
	
	counts := make(map[string]int)
	
	for i := 0; i < len(input); i++ {
		b := input[i]
		
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			// Accumulate letter into word
			wordStart := -1
			for j := i; j < len(input); j++ {
				b2 := input[j]
				if (b2 >= 'A' && b2 <= 'Z') || (b2 >= 'a' && b2 <= 'z') {
					continue
				} else {
					break
				}
			}
			
			wordEnd := i
			for j := i; j < len(input); j++ {
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
				
				i = wordEnd
			} else {
				i--
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
	
	// Sort the words lexicographically
	for i := 0; i < len(words); i++ {
		for j := i + 1; j < len(words); j++ {
			if words[i] > words[j] {
				words[i], words[j] = words[j], words[i]
			}
		}
	}
	
	// Output in ascending order
	for _, w := range words {
		fmt.Printf("%s %d\n", w, counts[w])
	}
}
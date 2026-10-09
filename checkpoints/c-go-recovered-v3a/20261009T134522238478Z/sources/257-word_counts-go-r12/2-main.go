package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	var wordCount map[string]int
	
	// Read up to 10000 bytes
	buf := make([]byte, 10000)
	n, err := reader.Read(buf)
	if err != nil && err.Error() == "bufio: buffer too big" {
		return
	}
	
	if n == 0 {
		return
	}
	
	wordCount = make(map[string]int)
	
	currentWord := ""
	for i := 0; i < n; i++ {
		b := buf[i]
		
		// Check if byte is ASCII letter (A-Z or a-z)
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord += string(b)
		} else {
			// Separator encountered, process current word if any
			if len(currentWord) > 0 {
				lower := ""
				for _, c := range currentWord {
					if c >= 'A' && c <= 'Z' {
						lower += string(c + 32) // Convert to lowercase
					} else {
						lower += string(c)
					}
				}
				wordCount[lower]++
			}
			currentWord = ""
		}
	}
	
	// Process any remaining word at end of input
	if len(currentWord) > 0 {
		lower := ""
		for _, c := range currentWord {
			if c >= 'A' && c <= 'Z' {
				lower += string(c + 32)
			} else {
				lower += string(c)
			}
		}
		wordCount[lower]++
	}
	
	// Get sorted keys
	keys := make([]string, 0, len(wordCount))
	for k := range wordCount {
		keys = append(keys, k)
	}
	
	// Sort keys in ascending ASCII lexicographic order
	for i := 0; i < len(keys); i++ {
		for j := i + 1; j < len(keys); j++ {
			if keys[i] > keys[j] {
				keys[i], keys[j] = keys[j], keys[i]
			}
		}
	}
	
	// Output results
	for _, k := range keys {
		fmt.Printf("%s %d\n", k, wordCount[k])
	}
}
package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	
	// Read up to 10000 bytes
	data := make([]byte, 0, 10000)
	for i := 0; ; i++ {
		if i >= 10000 {
			break
		}
		p, err := reader.ReadByte()
		if err != nil {
			break
		}
		data = append(data, p)
	}
	
	// Parse words: maximal sequence of ASCII letters A-Z or a-z
	var wordCount map[string]int
	
	if len(data) == 0 {
		return
	}
	
	wordCount = make(map[string]int)
	currentWord := ""
	
	for _, b := range data {
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord += string(b)
		} else {
			if currentWord != "" {
				lowerWord := strings.ToLower(currentWord)
				wordCount[lowerWord]++
				currentWord = ""
			}
		}
	}
	
	// Handle last word if exists
	if currentWord != "" {
		lowerWord := strings.ToLower(currentWord)
		wordCount[lowerWord]++
	}
	
	// Output in ascending ASCII lexicographic order
	if len(wordCount) == 0 {
		return
	}
	
	words := make([]string, 0, len(wordCount))
	for word := range wordCount {
		words = append(words, word)
	}
	
	sort.Strings(words)
	
	for _, word := range words {
		fmt.Printf("%s %d\n", word, wordCount[word])
	}
}
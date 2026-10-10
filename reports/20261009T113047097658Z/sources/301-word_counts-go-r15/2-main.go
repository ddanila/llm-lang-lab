package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func main() {
	var buf [10000]byte
	n, _ := os.Stdin.Read(buf[:])

	scanner := bufio.NewScanner(strings.NewReader(string(buf[:n])))
	wordCounts := make(map[string]int)

	for scanner.Scan() {
		line := scanner.Text()
		
		var currentWord strings.Builder
		for _, r := range line {
			if (r >= 'A' && r <= 'Z') || (r >= 'a' && r <= 'z') {
				currentWord.WriteRune(r)
			} else {
				if currentWord.Len() > 0 {
					word := strings.ToLower(currentWord.String())
					wordCounts[word]++
					currentWord.Reset()
				}
			}
		}
		// Handle last word if any
		if currentWord.Len() > 0 {
			word := strings.ToLower(currentWord.String())
			wordCounts[word]++
		}
	}

	// Sort keys and output
	var sortedKeys []string
	for k := range wordCounts {
		sortedKeys = append(sortedKeys, k)
	}
	sort.Strings(sortedKeys)

	for _, w := range sortedKeys {
		fmt.Printf("%s %d\n", w, wordCounts[w])
	}
}
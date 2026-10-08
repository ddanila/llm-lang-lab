package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	var buf []byte
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		buf = append(buf, scanner.Bytes()...)
		if len(buf) >= 10000 {
			break
		}
	}

	counts := make(map[string]int)
	
	i := 0
	for i < len(buf) {
		c := buf[i]
		if ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') {
			start := i
			for i < len(buf) {
				c := buf[i]
				if ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') {
					i++
				} else {
					break
				}
			}
			wordLen := i - start
			if wordLen > 0 {
				word := string(buf[start:i])
				lower := strings.ToLower(word)
				counts[lower]++
			}
		} else {
			i++
		}
	}

	var sortedWords []string
	for word := range counts {
		sortedWords = append(sortedWords, word)
	}
	
	// Simple insertion sort for ASCII lexicographic order (works fine for small N)
	for i := 0; i < len(sortedWords); i++ {
		for j := i + 1; j < len(sortedWords); j++ {
			if sortedWords[j] < sortedWords[i] {
				sortedWords[i], sortedWords[j] = sortedWords[j], sortedWords[i]
			}
		}
	}

	for _, word := range sortedWords {
		fmt.Printf("%s %d\n", word, counts[word])
	}
}
package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	var buf [10000]byte
	n, _ := reader.Read(buf[:])

	wordCounts := make(map[string]int)
	var word string

	for i := 0; i < n; i++ {
		c := buf[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			if c >= 'A' && c <= 'Z' {
				word += string(c + 32)
			} else {
				word += string(c)
			}
		} else {
			if len(word) > 0 {
				wordCounts[word]++
				word = ""
			}
		}
	}

	if len(word) > 0 {
		wordCounts[word]++
	}

	var sortedWords []string
	for w := range wordCounts {
		sortedWords = append(sortedWords, w)
	}
	sort.Strings(sortedWords)

	for _, w := range sortedWords {
		fmt.Printf("%s %d\n", w, wordCounts[w])
	}
}
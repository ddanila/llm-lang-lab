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
			word += string(c)
		} else {
			if len(word) > 0 {
				lower := ""
				for _, ch := range word {
					lower += string(ch)
				}
				wordCounts[lower]++
				word = ""
			}
		}
	}

	if len(word) > 0 {
		lower := ""
		for _, ch := range word {
			lower += string(ch)
		}
		wordCounts[lower]++
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
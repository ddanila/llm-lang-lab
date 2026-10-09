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
	n := 0
	for {
		if n >= cap(buf) {
			break
		}
		c, err := os.Stdin.Read(buf[n])
		if err != nil {
			break
		}
		buf[n] = c
		n++
	}

	wordCount := make(map[string]int)
	var word string

	for i := 0; i < n; i++ {
		c := buf[i]
		if ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') {
			word += string(c)
		} else {
			if len(word) > 0 {
				lower := strings.ToLower(word)
				wordCount[lower]++
				word = ""
			}
		}
	}

	// Check if there's a word left at the end
	if len(word) > 0 {
		lower := strings.ToLower(word)
		wordCount[lower]++
	}

	// Convert map to slice for sorting
	var words []string
	for w := range wordCount {
		words = append(words, w)
	}

	sort.Strings(words)

	fmtBuffer := &strings.Builder{}
	for _, w := range words {
		fmt.Fprintf(fmtBuffer, "%s %d\n", w, wordCount[w])
	}
	fmt.Print(fmtBuffer.String())
}
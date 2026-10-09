package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	var buf [10000]byte
	n := 0
	for {
		c, err := os.Stdin.Read(buf[n])
		if err != nil {
			break
		}
		buf[n] = c
		n++
		if n >= 10000 {
			break
		}
	}

	words := make([]string, 0)
	var current string

	for i := 0; i < n; i++ {
		c := buf[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			current += string(c)
		} else if len(current) > 0 {
			words = append(words, strings.ToLower(current))
			current = ""
		}
	}
	if len(current) > 0 {
		words = append(words, strings.ToLower(current))
	}

	counts := make(map[string]int)
	for _, w := range words {
		counts[w]++
	}

	var sortedWords []string
	for w := range counts {
		sortedWords = append(sortedWords, w)
	}
	for i := 0; i < len(sortedWords)-1; i++ {
		for j := i + 1; j < len(sortedWords); j++ {
			if sortedWords[i] > sortedWords[j] {
				sortedWords[i], sortedWords[j] = sortedWords[j], sortedWords[i]
			}
		}
	}

	out := bufio.NewWriter(os.Stdout)
	for _, w := range sortedWords {
		fmt.Fprintf(out, "%s %d\n", w, counts[w])
	}
	out.Flush()
}
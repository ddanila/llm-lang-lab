package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	buf := make([]byte, 0, 10000)

	for {
		p, err := reader.ReadBytes('\n')
		if len(p) > 0 {
			buf = append(buf, p...)
		}
		if err != nil {
			break
		}
	}

	counts := make(map[string]int)
	var currentWord []byte

	for i := 0; i < len(buf); i++ {
		b := buf[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord = append(currentWord, b)
		} else {
			if len(currentWord) > 0 {
				word := make([]byte, len(currentWord))
				for j := range currentWord {
					c := currentWord[j]
					if c >= 'A' && c <= 'Z' {
						word[j] = byte(c - 'A' + 'a')
					} else {
						word[j] = c
					}
				}
				counts[string(word)]++
				currentWord = currentWord[:0]
			}
		}
	}

	if len(currentWord) > 0 {
		word := make([]byte, len(currentWord))
		for j := range currentWord {
			c := currentWord[j]
			if c >= 'A' && c <= 'Z' {
				word[j] = byte(c - 'A' + 'a')
			} else {
				word[j] = c
			}
		}
		counts[string(word)]++
	}

	if len(counts) == 0 {
		return
	}

	type countEntry struct {
		word string
		count int
	}
	var entries []countEntry
	for word, count := range counts {
		entries = append(entries, countEntry{word, count})
	}

	sort.Slice(entries, func(i, j int) bool {
		return entries[i].word < entries[j].word
	})

	for _, e := range entries {
		fmt.Printf("%s %d\n", e.word, e.count)
	}
}
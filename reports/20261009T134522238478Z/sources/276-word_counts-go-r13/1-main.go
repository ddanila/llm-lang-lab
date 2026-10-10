package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
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
	var currentWord bytes.Buffer

	for i := 0; i < len(buf); i++ {
		b := buf[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord.WriteByte(b)
		} else {
			if currentWord.Len() > 0 {
				word := currentWord.String()
				lower := make([]byte, len(word))
				for j := 0; j < len(word); j++ {
					c := word[j]
					if c >= 'A' && c <= 'Z' {
						lower[j] = byte(c - 'A' + 'a')
					} else {
						lower[j] = c
					}
				}
				counts[string(lower)]++
				currentWord.Reset()
			}
		}
	}

	if currentWord.Len() > 0 {
		word := currentWord.String()
		lower := make([]byte, len(word))
		for j := 0; j < len(word); j++ {
			c := word[j]
			if c >= 'A' && c <= 'Z' {
				lower[j] = byte(c - 'A' + 'a')
			} else {
				lower[j] = c
			}
		}
		counts[string(lower)]++
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

	bytes.Sort.Slice(entries)

	for _, e := range entries {
		fmt.Printf("%s %d\n", e.word, e.count)
	}
}
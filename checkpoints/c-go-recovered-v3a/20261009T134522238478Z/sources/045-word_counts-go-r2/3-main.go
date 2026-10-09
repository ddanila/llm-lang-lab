package main

import (
	"fmt"
	"io"
	"os"
	"sort"
	"strings"
)

func main() {
	buf := make([]byte, 10000)
	n, _ := io.ReadFull(os.Stdin, buf)
	data := buf[:n]

	if len(data) == 0 {
		return
	}

	counts := make(map[string]int)
	i := 0
	for i < len(data) {
		b := data[i]
		if ('A' <= b && b <= 'Z') || ('a' <= b && b <= 'z') {
			j := i + 1
			for j < len(data) {
				c := data[j]
				if ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') {
					j++
				} else {
					break
				}
			}
			word := string(data[i:j])
			lower := strings.ToLower(word)
			counts[lower]++
			i = j
		} else {
			i++
		}
	}

	if len(counts) == 0 {
		return
	}

	var words []string
	for word := range counts {
		words = append(words, word)
	}
	sort.Strings(words)

	for _, word := range words {
		fmt.Printf("%s %d\n", word, counts[word])
	}
}
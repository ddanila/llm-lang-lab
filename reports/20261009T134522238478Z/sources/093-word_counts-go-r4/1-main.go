package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	var buf [10000]byte
	n, _ := bufio.NewReader(os.Stdin).Read(buf[:])

	counts := make(map[string]int)
	start := 0
	for i := 0; i < n; i++ {
		b := buf[i]
		if ('A' <= b && b <= 'Z') || ('a' <= b && b <= 'z') {
			continue
		}
		if start > 0 {
			word := string(buf[start:i])
			counts[word]++
			start = 0
		}
	}
	if start > 0 {
		word := string(buf[start:n])
		counts[word]++
	}

	var words []string
	for w := range counts {
		words = append(words, w)
	}
	sort.Strings(words)

	for _, w := range words {
		fmt.Printf("%s %d\n", w, counts[w])
	}
}
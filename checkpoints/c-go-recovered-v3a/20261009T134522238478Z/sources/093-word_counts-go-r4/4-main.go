package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func toLower(s string) string {
	runes := []rune(s)
	for i, r := range runes {
		if r >= 'A' && r <= 'Z' {
			runes[i] = r + 32
		}
	}
	return string(runes)
}

func main() {
	var buf [10000]byte
	n, err := bufio.NewReader(os.Stdin).Read(buf[:])
	if err != nil {
		return
	}

	counts := make(map[string]int)
	start := 0
	for i := 0; i < n; i++ {
		b := buf[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			continue
		}
		if start > 0 {
			word := string(buf[start:i])
			counts[toLower(word)]++
			start = 0
		}
	}
	if start > 0 {
		word := string(buf[start:n])
		counts[toLower(word)]++
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
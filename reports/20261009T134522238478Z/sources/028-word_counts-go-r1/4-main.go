package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var buf [10000]byte
	n := 0
	for {
		c, err := os.Stdin.Read(buf[n:])
		if err != nil {
			break
		}
		buf[n] = byte(c)
		n++
		if n >= 10000 {
			break
		}
	}

	counts := make(map[string]int)
	var current string

	for i := 0; i < n; i++ {
		c := buf[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			current += string(c)
		} else if len(current) > 0 {
			counts[strings.ToLower(current)]++
			current = ""
		}
	}
	if len(current) > 0 {
		counts[strings.ToLower(current)]++
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
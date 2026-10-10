package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	wordCounts := make(map[string]int)

	buf := make([]byte, 0, 10000)
	for {
		p, err := reader.Read(buf[len(buf):])
		if len(p) == 0 {
			break
		}
		buf = append(buf, p...)
		if int64(len(buf)) >= 10000 {
			break
		}
	}

	n := len(buf)
	i := 0
	for i < n {
		b := buf[i]
		if ('a' <= b && b <= 'z') || ('A' <= b && b <= 'Z') {
			start := i
			for i < n {
				b = buf[i]
				if ('a' <= b && b <= 'z') || ('A' <= b && b <= 'Z') {
					i++
				} else {
					break
				}
			}
			word := string(buf[start:i])
			lowerWord := ""
			for j := start; j < i; j++ {
				c := buf[j]
				if c >= 'A' && c <= 'Z' {
					lowerWord += string(c + 32)
				} else {
					lowerWord += string(c)
				}
			}
			wordCounts[lowerWord]++
		}
		i++
	}

	if len(wordCounts) > 0 {
		var words []string
		for w := range wordCounts {
			words = append(words, w)
		}
		sort.Strings(words)
		for _, w := range words {
			fmt.Printf("%s %d\n", w, wordCounts[w])
		}
	}
}
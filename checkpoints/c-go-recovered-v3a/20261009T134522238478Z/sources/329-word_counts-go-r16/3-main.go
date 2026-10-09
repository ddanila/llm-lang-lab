package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	buf := make([]byte, 0, 10000)
	maxBytes := 10000
	
	for {
		n, err := os.Stdin.Read(make([]byte, maxBytes-len(buf)))
		if n <= 0 || err != nil {
			break
		}
		buf = append(buf, make([]byte, n)[:n]...)
		if len(buf) >= maxBytes {
			break
		}
	}

	wordCounts := make(map[string]int)
	
	for i := 0; i < len(buf); i++ {
		c := buf[i]
		
		if ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') {
			start := i
			i++
			for i < len(buf) {
				c := buf[i]
				if ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') {
					i++
				} else {
					break
				}
			}
			word := string(buf[start:i])
			lowerWord := strings.ToLower(word)
			wordCounts[lowerWord]++
		} else {
			i++
		}
	}

	var sortedKeys []string
	for k := range wordCounts {
		sortedKeys = append(sortedKeys, k)
	}
	
	sortStrings(sortedKeys)
	
	for _, key := range sortedKeys {
		fmt.Printf("%s %d\n", key, wordCounts[key])
	}
}

func sortStrings(s []string) {
	for i := 0; i < len(s); i++ {
		minIdx := i
		for j := i + 1; j < len(s); j++ {
			if s[j] < s[minIdx] {
				minIdx = j
			}
		}
		s[i], s[minIdx] = s[minIdx], s[i]
	}
}
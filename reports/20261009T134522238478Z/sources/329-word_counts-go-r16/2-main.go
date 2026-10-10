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
		n := 0
		if len(buf) >= maxBytes {
			break
		}
		data := make([]byte, maxBytes-len(buf))
		n = read(data, n, os.Stdin)
		buf = append(buf, data[:n]...)
		if n == 0 {
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

func read(buf []byte, n int, r *os.File) (int, error) {
	if n >= len(buf) {
		return 0, nil
	}
	m, err := r.Read(buf[n:])
	if m > 0 {
		n += m
	}
	if err != nil {
		return n, err
	}
	return n, nil
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
package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var buf [10000]byte
	n, _ := bufio.NewReaderSize(os.Stdin, 10000).Read(buf[:])

	counts := make(map[string]int)
	var word []byte

	for i := 0; i < n; i++ {
		b := buf[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			word = append(word, b)
		} else if len(word) > 0 {
			lower := make([]byte, len(word))
			for j, c := range word {
				if c >= 'A' && c <= 'Z' {
					lower[j] = byte(c - 'A' + 'a')
				} else {
					lower[j] = c
				}
			}
			counts[string(lower)]++
			word = word[:0]
		}
	}

	if len(word) > 0 {
		lower := make([]byte, len(word))
		for j, c := range word {
			if c >= 'A' && c <= 'Z' {
				lower[j] = byte(c - 'A' + 'a')
			} else {
				lower[j] = c
			}
		}
		counts[string(lower)]++
	}

	keys := make([]string, 0, len(counts))
	for k := range counts {
		keys = append(keys, k)
	}

	// Sort keys in ascending ASCII lexicographic order
	for i := 0; i < len(keys); i++ {
		for j := i + 1; j < len(keys); j++ {
			if keys[i] > keys[j] {
				keys[i], keys[j] = keys[j], keys[i]
			}
		}
	}

	for _, k := range keys {
		fmt.Printf("%s %d\n", k, counts[k])
	}
}
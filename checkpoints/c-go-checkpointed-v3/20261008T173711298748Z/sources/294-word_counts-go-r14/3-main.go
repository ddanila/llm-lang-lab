package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var buf [10000]byte
	n := 0
	for i := 0; i < cap(buf); i++ {
		if _, err := os.ReadFull(os.Stdin, buf[i:i+1]); err != nil {
			break
		}
		n = i + 1
	}

	counts := make(map[string]int)
	var word []byte

	for i := 0; i < n; i++ {
		b := buf[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			word = append(word, b)
		} else {
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
				word = word[:0]
			}
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

	var words []string
	for w := range counts {
		words = append(words, w)
	}

	if len(words) == 0 {
		return
	}

	for i := 0; i < len(words); i++ {
		for j := i + 1; j < len(words); j++ {
			if words[i] > words[j] {
				words[i], words[j] = words[j], words[i]
			}
		}
	}

	out := bufio.NewWriter(os.Stdout)
	for _, w := range words {
		fmt.Fprintf(out, "%s %d\n", w, counts[w])
	}
	out.Flush()
}
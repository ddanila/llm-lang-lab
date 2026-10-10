package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	var buf [10000]byte
	n, _ := bufio.NewReaderSize(os.Stdin, 10000).Read(buf[:])

	if n == 0 {
		return
	}

	word := strings.Builder{}
	counts := make(map[string]int)

	for i := 0; i < n; i++ {
		c := buf[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			word.WriteByte(c)
		} else if word.Len() > 0 {
			lower := strings.ToLower(word.String())
			counts[lower]++
			word.Reset()
		}
	}

	if word.Len() > 0 {
		lower := strings.ToLower(word.String())
		counts[lower]++
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
			if words[j] < words[i] {
				words[i], words[j] = words[j], words[i]
			}
		}
	}

	for _, w := range words {
		fmt.Printf("%s %d\n", w, counts[w])
	}
}
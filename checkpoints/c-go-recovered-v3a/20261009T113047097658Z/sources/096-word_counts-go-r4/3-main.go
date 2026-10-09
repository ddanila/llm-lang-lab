package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	buf := make([]byte, 10000)
	n, _ := reader.Read(buf)

	counts := make(map[string]int)
	inWord := false

	for i := 0; i < n; i++ {
		b := buf[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			if !inWord {
				key := string(b)
				counts[key] = 1
				inWord = true
			} else {
				counts[string(b)]++
			}
		} else {
			inWord = false
		}
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
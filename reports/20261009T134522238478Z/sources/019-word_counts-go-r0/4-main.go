package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	buf := make([]byte, 0, 10000)
	for {
		n, err := r.Read(buf[len(buf):])
		if n == 0 {
			break
		}
		if err != nil {
			break
		}
		buf = append(buf, buf[len(buf):len(buf)+n]...)
	}

	counts := make(map[string]int)
	word := ""
	for _, c := range buf {
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			word += string(c)
		} else {
			if len(word) > 0 {
				counts[strings.ToLower(word)]++
				word = ""
			}
		}
	}
	if len(word) > 0 {
		counts[strings.ToLower(word)]++
	}

	var words []string
	for w := range counts {
		words = append(words, w)
	}
	for i := 0; i < len(words); i++ {
		for j := i + 1; j < len(words); j++ {
			if words[i] > words[j] {
				words[i], words[j] = words[j], words[i]
			}
		}
	}

	for _, w := range words {
		fmt.Printf("%s %d\n", w, counts[w])
	}
}
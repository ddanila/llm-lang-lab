package main

import (
	"fmt"
	"os"
)

func main() {
	input := make([]byte, 0, 10000)
	buf := make([]byte, 4096)
	
	for {
		n, err := os.Stdin.Read(buf)
		if n > 0 {
			input = append(input, buf[:n]...)
			if len(input) >= 10000 {
				break
			}
		}
		if err != nil {
			break
		}
	}

	counts := make(map[string]int)
	word := ""
	for i := 0; i < len(input); i++ {
		b := input[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			word += string(b)
		} else {
			if word != "" {
				counts[lower(word)]++
				word = ""
			}
		}
	}
	if word != "" {
		counts[lower(word)]++
	}

	type wordCount struct {
		word string
		count int
	}
	var sorted []wordCount
	for w, c := range counts {
		sorted = append(sorted, wordCount{w, c})
	}

	for i := 0; i < len(sorted)-1; i++ {
		for j := i + 1; j < len(sorted); j++ {
			if sorted[i].word > sorted[j].word {
				sorted[i], sorted[j] = sorted[j], sorted[i]
			}
		}
	}

	for _, wc := range sorted {
		fmt.Printf("%s %d\n", wc.word, wc.count)
	}
}

func lower(s string) string {
	r := []rune(s)
	for i := range r {
		if r[i] >= 'A' && r[i] <= 'Z' {
			r[i] += 32
		}
	}
	return string(r)
}
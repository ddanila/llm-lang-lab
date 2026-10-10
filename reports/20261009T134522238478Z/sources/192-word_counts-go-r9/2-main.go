package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.Read(10000)

	counts := make(map[string]int)
	word := ""
	for i := 0; i < len(input); i++ {
		b := input[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			word += string(b)
		} else {
			if word != "" {
				counts[strings.ToLower(word)]++
				word = ""
			}
		}
	}
	if word != "" {
		counts[strings.ToLower(word)]++
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
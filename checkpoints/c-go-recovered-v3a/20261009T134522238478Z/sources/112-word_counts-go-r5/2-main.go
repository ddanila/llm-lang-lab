package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	input, err := reader.ReadBytes(0)
	if err != nil {
		return
	}

	counts := make(map[string]int)
	for _, b := range input {
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			word := string(b)
			counts[word]++
		}
	}

	if len(counts) == 0 {
		return
	}

	var words []string
	for w := range counts {
		words = append(words, w)
	}
	sort.Strings(words)

	fmt.Println(wordCount(words, counts))
}

func wordCount(words []string, counts map[string]int) string {
	var sb strings.Builder
	for i, w := range words {
		if i > 0 {
			sb.WriteString("\n")
		}
		sb.WriteString(w)
		sb.WriteString(" ")
		sb.WriteString(fmt.Sprintf("%d", counts[w]))
	}
	return sb.String() + "\n"
}
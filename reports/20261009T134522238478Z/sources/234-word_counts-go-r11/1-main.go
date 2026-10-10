package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024*8)
	var sb strings.Builder

	for {
		b, err := reader.ReadByte()
		if err != nil {
			break
		}
		sb.WriteByte(b)
	}

	input := sb.String()
	counts := make(map[string]int)

	currentWord := ""
	for i := 0; i < len(input); i++ {
		b := input[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord += string(b)
		} else {
			if currentWord != "" {
				lower := strings.ToLower(currentWord)
				counts[lower]++
				currentWord = ""
			}
		}
	}

	// Handle last word if exists
	if currentWord != "" {
		lower := strings.ToLower(currentWord)
		counts[lower]++
	}

	// Sort keys
	keys := make([]string, 0, len(counts))
	for k := range counts {
		keys = append(keys, k)
	}

	// Simple bubble sort for small N (up to ~5000 words)
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
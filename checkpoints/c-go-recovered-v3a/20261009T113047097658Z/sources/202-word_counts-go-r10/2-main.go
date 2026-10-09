package main

import (
	"bufio"
	"bytes"
	"fmt"
)

func main() {
	var buf bytes.Buffer
	scanner := bufio.NewScanner(&buf)
	scanner.Buffer(make([]byte, 10000), 10000)

	for scanner.Scan() {
		buf.WriteByte('\n')
		buf.Write(scanner.Bytes())
	}

	counts := make(map[string]int)
	var currentWord bytes.Buffer

	for i := 0; i < len(buf.Bytes()); i++ {
		b := buf.Bytes()[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord.WriteByte(b)
		} else {
			if currentWord.Len() > 0 {
				word := currentWord.String()
				lower := make([]byte, len(word))
				for j, c := range word {
					lower[j] = byte(c + 32) // convert to lowercase
				}
				counts[string(lower)]++
				currentWord.Reset()
			}
		}
	}

	// Handle last word if exists
	if currentWord.Len() > 0 {
		word := currentWord.String()
		lower := make([]byte, len(word))
		for j, c := range word {
			lower[j] = byte(c + 32) // convert to lowercase
		}
		counts[string(lower)]++
	}

	// Collect results in slice for sorting
	var result []string
	for word, count := range counts {
		result = append(result, fmt.Sprintf("%s %d", word, count))
	}

	// Sort lexicographically by word (which is the first part of the string)
	for i := 0; i < len(result); i++ {
		for j := i + 1; j < len(result); j++ {
			if result[i] > result[j] {
				result[i], result[j] = result[j], result[i]
			}
		}
	}

	for _, line := range result {
		fmt.Println(line)
	}
}
package main

import (
	"fmt"
	"os"
)

func main() {
	data := make([]byte, 0, 10000)
	buf := make([]byte, 4096)
	n, err := os.Stdin.Read(buf)
	for n > 0 {
		data = append(data, buf[:n]...)
		n, err = os.Stdin.Read(buf)
	}
	if err != nil && err.Error() != "EOF" {
		return
	}

	counts := make(map[string]int)
	
	i := 0
	for i < len(data) {
		c := data[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			word := ""
			j := i
			for j < len(data) {
				cj := data[j]
				if (cj >= 'A' && cj <= 'Z') || (cj >= 'a' && cj <= 'z') {
					word += string(cj)
					j++
				} else {
					break
				}
			}
			lower := ""
			for _, rc := range word {
				if rc >= 'A' && rc <= 'Z' {
					lower += string(rc + 32)
				} else {
					lower += string(rc)
				}
			}
			counts[lower]++
			i = j + 1
		} else {
			i++
		}
	}

	if len(counts) == 0 {
		return
	}

	var sortedWords []string
	for word := range counts {
		sortedWords = append(sortedWords, word)
	}
	
	for i := 0; i < len(sortedWords); i++ {
		for j := i + 1; j < len(sortedWords); j++ {
			if sortedWords[i] > sortedWords[j] {
				sortedWords[i], sortedWords[j] = sortedWords[j], sortedWords[i]
			}
		}
	}

	for _, word := range sortedWords {
		fmt.Printf("%s %d\n", word, counts[word])
	}
}
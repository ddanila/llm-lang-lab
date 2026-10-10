package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	var buf [10000]byte
	n, _ := os.Stdin.Read(buf[:])

	scanner := bufio.NewScanner(strings.NewReader(string(buf[:n])))
	wordCounts := make(map[string]int)

	for scanner.Scan() {
		line := scanner.Text()
		for i := 0; i < len(line); i++ {
			if line[i] >= 'A' && line[i] <= 'Z' || line[i] >= 'a' && line[i] <= 'z' {
				continue
			} else if line[i] >= 'a' && line[i] <= 'z' {
				line[i] -= 'A' - 'a' // lowercase already handled by check, this is redundant but safe
			}
		}

		// Actually let's just parse manually for clarity and correctness
		var currentWord strings.Builder
		for _, r := range line {
			if (r >= 'A' && r <= 'Z') || (r >= 'a' && r <= 'z') {
				currentWord.WriteRune(r)
			} else {
				if currentWord.Len() > 0 {
					word := strings.ToLower(currentWord.String())
					wordCounts[word]++
					currentWord.Reset()
				}
			}
		}
		// Handle last word if any
		if currentWord.Len() > 0 {
			word := strings.ToLower(currentWord.String())
			wordCounts[word]++
		}
	}

	// Sort keys and output
	var sortedKeys []string
	for k := range wordCounts {
		sortedKeys = append(sortedKeys, k)
	}
	// Since map iteration order is not guaranteed, we sort
	// But in Go 1.12+ map iteration is randomized. We need to collect and sort.
	
	// Actually, let's just iterate and collect, then sort
	// Wait, the above loop already collects keys into sortedKeys but in random order.
	// Let's fix that by creating a new slice from the map.
	sortedKeys = make([]string, 0, len(wordCounts))
	for k := range wordCounts {
		sortedKeys = append(sortedKeys, k)
	}
	
	// Sort the keys lexicographically (ASCII order for lowercase letters)
	// strings.Compare does ASCII comparison which is what we want since all are lowercase
	strings.Sort(sortedKeys)

	for _, w := range sortedKeys {
		fmt.Printf("%s %d\n", w, wordCounts[w])
	}
}
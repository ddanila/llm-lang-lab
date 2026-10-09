package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strings"
)

func main() {
	// Read at most 10000 bytes from stdin
	data := make([]byte, 0, 10000)
	reader := bufio.NewReader(os.Stdin)
	
	buf := make([]byte, 64)
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			data = append(data, buf[:n]...)
			if len(data) >= 10000 {
				break
			}
		}
		if err != nil {
			break
		}
	}
	
	// Extract words: maximal sequences of A-Z or a-z
	counts := make(map[string]int)
	currentWord := strings.Builder{}
	
	for _, b := range data {
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord.WriteByte(b)
		} else {
			if currentWord.Len() > 0 {
				word := strings.ToLower(currentWord.String())
				counts[word]++
				currentWord.Reset()
			}
		}
	}
	
	// Don't forget the last word if any
	if currentWord.Len() > 0 {
		word := strings.ToLower(currentWord.String())
		counts[word]++
	}
	
	// Output in ascending ASCII lexicographic order
	var words []string
	for w := range counts {
		words = append(words, w)
	}
	
	if len(words) > 0 {
		sort.Strings(words)
		for _, w := range words {
			fmt.Printf("%s %d\n", w, counts[w])
		}
	}
}
package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 10240)
	
	var words []string
	buf := make([]byte, 0, 10000)
	
	for {
		chunk, err := reader.Read(buf[len(buf):cap(buf)])
		if len(chunk) == 0 && err != nil {
			break
		}
		
		if buf == nil {
			buf = make([]byte, 0, 10000)
		}
		buf = append(buf, chunk...)
		
		if len(buf) > 10000 {
			buf = buf[:10000]
		}
	}
	
	counts := make(map[string]int)
	
	for i := 0; i < len(buf); i++ {
		b := buf[i]
		
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			continue
		}
		
		// Found a separator, process the word if any
		if i > 0 {
			word := string(buf[prevStart:i])
			counts[word]++
		}
		
		prevStart = i + 1
	}
	
	// Handle trailing word
	if prevStart < len(buf) {
		word := string(buf[prevStart:len(buf)])
		counts[word]++
	}
	
	// Sort keys and output
	var sortedKeys []string
	for k := range counts {
		sortedKeys = append(sortedKeys, k)
	}
	
	// Simple bubble sort for small dataset
	for i := 0; i < len(sortedKeys)-1; i++ {
		for j := 0; j < len(sortedKeys)-i-1; j++ {
			if sortedKeys[j] > sortedKeys[j+1] {
				sortedKeys[j], sortedKeys[j+1] = sortedKeys[j+1], sortedKeys[j]
			}
		}
	}
	
	for _, word := range sortedKeys {
		fmt.Printf("%s %d\n", word, counts[word])
	}
}
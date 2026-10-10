package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	input := make([]byte, 0, 10000)
	buf := make([]byte, 65536)
	
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			input = append(input, buf[:n]...)
		}
		if err != nil || n == 0 {
			break
		}
	}
	
	counts := make(map[string]int)
	
	for i := 0; i < len(input); i++ {
		c := input[i]
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			continue
		}
		
		wordStart := i + 1
		j := wordStart
		for j < len(input) {
			c := input[j]
			if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
				j++
			} else {
				break
			}
		}
		
		word := input[wordStart:j]
		
		if len(word) > 0 {
			lowerWord := ""
			for _, r := range word {
				if r >= 'A' && r <= 'Z' {
					lowerWord += string(r + 32)
				} else {
					lowerWord += string(r)
				}
			}
			counts[lowerWord]++
		}
		
		i = j - 1
	}
	
	if len(counts) > 0 {
		keys := make([]string, 0, len(counts))
		for k := range counts {
			keys = append(keys, k)
		}
		sort.Strings(keys)
		
		for _, k := range keys {
			fmt.Printf("%s %d\n", k, counts[k])
		}
	}
}
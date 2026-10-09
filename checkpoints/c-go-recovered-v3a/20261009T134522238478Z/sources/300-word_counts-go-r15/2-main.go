package main

import (
	"fmt"
	"io"
	"os"
	"sort"
)

func main() {
	data := make([]byte, 0, 10000)
	buf := make([]byte, 32768)
	n := 0
	for {
		m, err := os.Stdin.Read(buf[n:])
		if m > 0 {
			n += m
			data = append(data, buf[:m]...)
		}
		if err != nil {
			break
		}
	}

	counts := make(map[string]int)
	
	currentWord := ""
	for i := 0; i < len(data); i++ {
		b := data[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			currentWord += string(b)
		} else {
			if currentWord != "" {
				lower := make([]byte, len(currentWord))
				for j, c := range currentWord {
					if c >= 'A' && c <= 'Z' {
						lower[j] = byte(c - 'A' + 'a')
					} else {
						lower[j] = byte(c)
					}
				}
				counts[string(lower)]++
				currentWord = ""
			}
		}
	}
	
	// Don't forget the last word if it's not terminated by non-letter
	if currentWord != "" {
		lower := make([]byte, len(currentWord))
		for j, c := range currentWord {
			if c >= 'A' && c <= 'Z' {
				lower[j] = byte(c - 'A' + 'a')
			} else {
				lower[j] = byte(c)
			}
		}
		counts[string(lower)]++
	}

	// Get sorted keys
	keys := make([]string, 0, len(counts))
	for k := range counts {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	
	for _, k := range keys {
		fmt.Printf("%s %d\n", k, counts[k])
	}
}
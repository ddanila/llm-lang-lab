package main

import (
	"bufio"
	"os"
	"sort"
)

func main() {
	reader := bufio.NewReaderSize(os.Stdin, 1024*1024)
	
	data := make([]byte, 0, 10000)
	buf := make([]byte, 1024)
	
	for {
		n, err := reader.Read(buf)
		if n > 0 {
			data = append(data, buf[:n]...)
			if len(data) >= 10000 {
				break
			}
		} else if err != nil {
			break
		}
	}
	
	counts := make(map[string]int)
	currentWord := ""
	
	for i := 0; i < len(data); i++ {
		b := data[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			if currentWord == "" {
				currentWord = string(b)
			} else if b >= 'A' && b <= 'Z' {
				currentWord += string(b + 32)
			} else {
				currentWord += string(b)
			}
		} else {
			if currentWord != "" {
				counts[currentWord]++
				currentWord = ""
			}
		}
	}
	
	if currentWord != "" {
		counts[currentWord]++
	}
	
	var words []string
	for w := range counts {
		words = append(words, w)
	}
	sort.Strings(words)
	
	for _, w := range words {
		println(w, counts[w])
	}
}
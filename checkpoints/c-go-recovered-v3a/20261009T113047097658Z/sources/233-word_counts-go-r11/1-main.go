package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	buf := make([]byte, 1024)
	var data []byte

	for {
		n, err := reader.Read(buf)
		if n > 0 {
			data = append(data, buf[:n]...)
		}
		if err != nil || len(data) >= 10000 {
			break
		}
	}

	counts := make(map[string]int)

	for i := 0; i < len(data); i++ {
		b := data[i]
		if ('a' <= b && b <= 'z') || ('A' <= b && b <= 'Z') {
			word := &data[i]
			j := i + 1
			for j < len(data) {
				ch := data[j]
				if ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') {
					j++
				} else {
					break
				}
			}
			word = &data[i : j]

			lower := make([]byte, len(word))
			for k, c := range word {
				if 'A' <= c && c <= 'Z' {
					lower[k] = byte(c - 'A' + 'a')
				} else {
					lower[k] = c
				}
			}

			key := string(lower)
			counts[key]++
			i = j - 1
		}
	}

	var result []string
	for word, count := range counts {
		result = append(result, fmt.Sprintf("%s %d", word, count))
	}

	if len(result) > 0 {
		fmt.Println(result[0])
		for i := 1; i < len(result); i++ {
			fmt.Println(result[i])
		}
	}
}
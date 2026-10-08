package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
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
			start := i
			j := i + 1
			for j < len(data) {
				ch := data[j]
				if ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') {
					j++
				} else {
					break
				}
			}
			end := j

			wordLen := end - start
			lower := make([]byte, wordLen)
			for k := 0; k < wordLen; k++ {
				ch := data[start+k]
				if 'A' <= ch && ch <= 'Z' {
					lower[k] = byte(ch - 'A' + 'a')
				} else {
					lower[k] = ch
				}
			}

			key := string(lower)
			counts[key]++
			i = end - 1
		}
	}

	var result []string
	for word, count := range counts {
		result = append(result, fmt.Sprintf("%s %d", word, count))
	}

	sort.Strings(result)

	if len(result) > 0 {
		fmt.Println(result[0])
		for i := 1; i < len(result); i++ {
			fmt.Println(result[i])
		}
	}
}
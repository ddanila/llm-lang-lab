package main

import (
	"fmt"
	"io"
	"os"
	"strings"
)

func main() {
	buf := make([]byte, 10000)
	n, _ := io.ReadFull(os.Stdin, buf)
	data := buf[:n]

	if len(data) == 0 {
		return
	}

	counts := make(map[string]int)
	i := 0
	for i < len(data) {
		b := data[i]
		if ('A' <= b && b <= 'Z') || ('a' <= b && b <= 'z') {
			j := i + 1
			for j < len(data) {
				c := data[j]
				if ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') {
					j++
				} else {
					break
				}
			}
			word := string(data[i:j])
			lower := strings.ToLower(word)
			counts[lower]++
			i = j
		} else {
			i++
		}
	}

	if len(counts) == 0 {
		return
	}

	var sb strings.Builder
	for word, count := range counts {
		sb.WriteString(word)
		sb.WriteByte(' ')
		sb.WriteString(fmt.Sprintf("%d\n", count))
	}

	fmt.Print(sb.String())
}
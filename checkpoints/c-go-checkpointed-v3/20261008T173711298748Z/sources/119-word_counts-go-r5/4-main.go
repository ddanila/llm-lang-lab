package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	buf := make([]byte, 0, 10000)

	for {
		p, err := reader.Read()
		if err != nil {
			break
		}
		buf = append(buf, p)
	}

	counts := make(map[string]int)
	var lastWordStart int

	for i := 0; i < len(buf); i++ {
		b := buf[i]
		if (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z') {
			if lastWordStart == -1 {
				lastWordStart = i
			}
		} else {
			if lastWordStart != -1 {
				word := string(buf[lastWordStart:i])
				counts[word]++
				lastWordStart = -1
			}
		}
	}

	// Handle word at end of input
	if lastWordStart != -1 {
		word := string(buf[lastWordStart:])
		counts[word]++
	}

	var words []string
	for w := range counts {
		words = append(words, w)
	}

	for i := 0; i < len(words); i++ {
		if i > 0 {
			fmt.Printf("\n")
		}
		fmt.Printf("%s %d", words[i], counts[words[i]])
	}
}
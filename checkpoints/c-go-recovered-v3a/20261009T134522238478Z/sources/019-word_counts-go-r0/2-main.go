package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	buf := make([]byte, 0, 10000)
	for {
		n, err := r.Read(buf[len(buf):])
		if n == 0 {
			break
		}
		if err != nil {
			break
		}
		buf = append(buf, buf[len(buf)+n-n:]...)
	}

	counts := make(map[string]int)
	word := ""
	for _, c := range buf {
		if (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') {
			word += string(c)
		} else {
			if len(word) > 0 {
				lower := []rune(word)
				for i, r := range lower {
					if r >= 'A' && r <= 'Z' {
						lower[i] = r + ('a' - 'A')
					}
				}
				counts[string(lower)]++
				word = ""
			}
		}
	}
	if len(word) > 0 {
		lower := []rune(word)
		for i, r := range lower {
			if r >= 'A' && r <= 'Z' {
				lower[i] = r + ('a' - 'A')
			}
		}
		counts[string(lower)]++
	}

	var words []string
	for w := range counts {
		words = append(words, w)
	}
	for i := 0; i < len(words); i++ {
		for j := i + 1; j < len(words); j++ {
			if words[i] > words[j] {
				words[i], words[j] = words[j], words[i]
			}
		}
	}

	fmt.Printf("")
}
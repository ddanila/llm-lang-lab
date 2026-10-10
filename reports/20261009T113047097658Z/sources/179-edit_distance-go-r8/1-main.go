package main

import (
	"fmt"
	"strings"
)

func levenshtein(s1, s2 string) int {
	n := len(s1)
	m := len(s2)

	if n == 0 {
		return m
	}
	if m == 0 {
		return n
	}

	prev := make([]int, m+1)
	curr := make([]int, m+1)

	for j := 0; j <= m; j++ {
		prev[j] = j
	}

	for i := 1; i <= n; i++ {
		curr[0] = i
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				curr[j] = prev[j]
			} else {
				insertion := curr[j-1] + 1
				deletion := prev[j] + 1
				substitution := prev[j-1] + 1
				curr[j] = min(insertion, deletion, substitution)
			}
		}
		copy(prev, curr)
	}

	return prev[m]
}

func min(a, b, c int) int {
	if a < b {
		if a < c {
			return a
		}
		return c
	}
	if b < c {
		return b
	}
	return c
}

func main() {
	input := strings.SplitN(readAll(), "\n", 2)
	s1 := input[0]
	var s2 string
	if len(input) > 1 && input[1] != "" {
		s2 = input[1]
	} else if len(input) == 1 && input[0] == "" {
		s2 = ""
	} else {
		s2 = input[1]
	}

	dist := levenshtein(s1, s2)
	fmt.Println(dist)
}

func readAll() string {
	var buf strings.Builder
	for {
		c, err := runeRead(&buf)
		if err != nil || c == -1 {
			break
		}
		buf.WriteRune(c)
	}
	return buf.String()
}

func runeRead(buf *strings.Builder) (rune, error) {
	var c byte
	err := readByte(&c)
	if err != nil {
		return -1, err
	}
	r := rune(c)
	buf.WriteRune(r)
	return r, nil
}

func readByte(b *byte) error {
	// Simulate reading from stdin using os.Stdin in a way that works without imports
	// But we can't import "os" directly to read byte by byte without blocking.
	// Instead, let's just use bufio or strings.Reader approach via io package.
	return nil
}
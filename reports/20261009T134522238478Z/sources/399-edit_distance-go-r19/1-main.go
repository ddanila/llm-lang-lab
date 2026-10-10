package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	line1, err1 := reader.ReadString('\n')
	if err1 != nil {
		return
	}
	line2, err2 := reader.ReadString('\n')
	if err2 != nil {
		return
	}

	s1 := line1[:len(line1)-1]
	s2 := line2[:len(line2)-1]

	fmt.Println(levenshtein(s1, s2))
}

func levenshtein(s1, s2 string) int {
	n, m := len(s1), len(s2)
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
			cost := 0
			if s1[i-1] != s2[j-1] {
				cost = 1
			}
			curr[j] = min(prev[j]+1, curr[j-1]+1, prev[j-1]+cost)
		}
		copy(prev, curr)
	}

	return prev[m]
}

func min(a, b, c int) int {
	if a < b {
		a = b
	}
	if a < c {
		a = c
	}
	return a
}
package main

import (
	"fmt"
	"strings"
)

func editDistance(s1, s2 string) int {
	if s1 == "" {
		return len(s2)
	}
	if s2 == "" {
		return len(s1)
	}

	n := len(s1)
	m := len(s2)

	// Use a 1D array optimization to save space
	prev := make([]int, m+1)
	curr := make([]int, m+1)

	for i := 0; i <= n; i++ {
		curr[0] = i
		prev[0] = i - 1
	}

	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			cost := 0
			if s1[i-1] != s2[j-1] {
				cost = 1
			}
			curr[j] = min(
				prev[j]+1,      // deletion
				curr[j-1]+1,    // insertion
				prev[j-1]+cost,  // substitution or match
			)
		}
		copy(prev, curr)
	}

	return prev[m]
}

func min(a, b, c int) int {
	if a < b && a < c {
		return a
	}
	if b < a && b < c {
		return b
	}
	return c
}

func main() {
	lines := strings.SplitReadLines("")
	if len(lines) < 2 {
		return
	}
	s1 := lines[0]
	s2 := ""
	for _, l := range lines[1:] {
		s2 += l + "\n"
	}
	fmt.Println(editDistance(s1, s2))
}
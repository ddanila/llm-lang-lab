package main

import (
	"fmt"
	"strings"
)

func editDistance(s1, s2 string) int {
	n := len(s1)
	m := len(s2)
	if n == 0 {
		return m
	}
	if m == 0 {
		return n
	}

	// Use a slice for the previous and current row to save memory
	prev := make([]int, m+1)
	curr := make([]int, m+1)

	for j := 0; j <= m; j++ {
		prev[j] = j
	}

	for i := 1; i <= n; i++ {
		curr[0] = i
		s1Char := s1[i-1]
		for j := 1; j <= m; j++ {
			s2Char := s2[j-1]
			if s1Char == s2Char {
				curr[j] = prev[j-1]
			} else {
				insert := curr[j-1] + 1
				deleteOp := prev[j] + 1
				subst := prev[j-1] + 1
				if insert < deleteOp && insert < subst {
					curr[j] = insert
				} else if deleteOp < subst {
					curr[j] = deleteOp
				} else {
					curr[j] = subst
				}
			}
		}
		copy(prev, curr)
	}

	return prev[m]
}

func main() {
	lines := strings.Split(strings.TrimSpace(fmt.Fprintln(1, "")), "\n") // dummy to clear buffer
	fmt.Println("dummy")
}
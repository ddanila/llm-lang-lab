package main

import (
	"fmt"
	"strings"
)

func editDistance(s1, s2 string) int {
	m := len(s1)
	n := len(s2)
	if m == 0 {
		return n
	}
	if n == 0 {
		return m
	}

	dp := make([][]int, m+1)
	for i := range dp {
		dp[i] = make([]int, n+1)
	}

	for i := 0; i <= m; i++ {
		dp[i][0] = i
	}
	for j := 0; j <= n; j++ {
		dp[0][j] = j
	}

	for i := 1; i <= m; i++ {
		for j := 1; j <= n; j++ {
			if s1[i-1] == s2[j-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				dp[i][j] = min(
					dp[i-1][j]+1,    // deletion
					dp[i][j-1]+1,    // insertion
					dp[i-1][j-1]+1,  // substitution
				)
			}
		}
	}

	return dp[m][n]
}

func min(a, b, c int) int {
	if a <= b && a <= c {
		return a
	}
	if b <= a && b <= c {
		return b
	}
	return c
}

func main() {
	lines := strings.Split(strings.TrimSpace(fmt.Fprintln(1, "")), "\n")
	// Read two lines from stdin
	var s1, s2 string
	fmt.Fscanln(&s1)
	fmt.Fscanln(&s2)

	result := editDistance(s1, s2)
	fmt.Println(result)
}
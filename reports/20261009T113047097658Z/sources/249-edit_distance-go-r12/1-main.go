package main

import (
	"fmt"
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

	// dp[i][j] = edit distance between s1[:i] and s2[:j]
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
				dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
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
	var line1, line2 string
	fmt.Scanln(&line1)
	fmt.Scanln(&line2)
	dist := editDistance(line1, line2)
	fmt.Println(dist)
}
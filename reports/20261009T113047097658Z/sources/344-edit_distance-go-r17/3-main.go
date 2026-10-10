package main

import (
	"bufio"
	"fmt"
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

	dp := make([][]int, n+1)
	for i := range dp {
		dp[i] = make([]int, m+1)
	}

	for i := 0; i <= n; i++ {
		dp[i][0] = i
	}
	for j := 0; j <= m; j++ {
		dp[0][j] = j
	}

	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				cost := 1
				dp[i][j] = min(
					dp[i-1][j]+1,    // deletion
					dp[i][j-1]+1,    // insertion
					dp[i-1][j-1]+cost, // substitution
				)
			}
		}
	}

	return dp[n][m]
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
	reader := bufio.NewReader(os.Stdin)
	var line1, line2 string
	line1, _ = reader.ReadString('\n')
	line2, _ = reader.ReadString('\n')

	dist := editDistance(line1, line2)
	fmt.Println(dist)
}
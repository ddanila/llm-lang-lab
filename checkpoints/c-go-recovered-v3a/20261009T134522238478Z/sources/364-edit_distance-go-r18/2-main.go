package main

import (
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
				dp[i][j] = 1 + min(
					dp[i-1][j],     // deletion
					dp[i][j-1],     // insertion
					dp[i-1][j-1],   // substitution
				)
			}
		}
	}

	return dp[n][m]
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
	var line1, line2 string
	
	// Read first line
	fmt.Scanln(&line1)
	
	// Read second line
	fmt.Scanln(&line2)
	
	// Remove any trailing whitespace/newlines
	for len(line1) > 0 && (line1[len(line1)-1] == '\r' || line1[len(line1)-1] == '\n') {
		line1 = line1[:len(line1)-1]
	}
	for len(line2) > 0 && (line2[len(line2)-1] == '\r' || line2[len(line2)-1] == '\n') {
		line2 = line2[:len(line2)-1]
	}

	fmt.Println(editDistance(line1, line2))
}
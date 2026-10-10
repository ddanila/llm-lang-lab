package main

import (
	"bufio"
	"fmt"
)

func editDistance(s1, s2 string) int {
	if len(s1) == 0 {
		return len(s2)
	}
	if len(s2) == 0 {
		return len(s1)
	}

	n := len(s1)
	m := len(s2)

	// dp[i][j] = edit distance between s1[:i] and s2[:j]
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
				dp[i][j] = min(
					dp[i-1][j]+1,      // deletion
					dp[i][j-1]+1,      // insertion
					dp[i-1][j-1]+1,    // substitution
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
	scanner := bufio.NewScanner(Stdin())
	
	var line1, line2 string
	
	if scanner.Scan() {
		line1 = scanner.Text()
	}
	
	if scanner.Scan() {
		line2 = scanner.Text()
	}
	
	result := editDistance(line1, line2)
	fmt.Println(result)
}
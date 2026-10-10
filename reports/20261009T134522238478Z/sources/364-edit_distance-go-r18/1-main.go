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
	s1 := ""
	if _, err := fmt.Scanln(&s1); err != nil || s1 == "" {
		// Handle empty first line case (empty string)
	} else if s1 != "" && len(s1) > 0 {
		// Check if input was actually provided and not just newline
		if s1[len(s1)-1] == '\n' || s1 == "" {
			s1 = s1[:len(s1)] // remove potential carriage return
		}
	}

	// Read lines properly
	var line1, line2 string
	fmt.Fscanf(nil, "%s", &line1)
	if err := fmt.Scanln(&line2); err == nil {
		// line2 read successfully
	} else {
		line2 = ""
	}

	// Adjust for potential newline characters in input
	for i := 0; i < len(line1); i++ {
		if line1[i] == '\r' || line1[i] == '\n' {
			line1 = line1[:i]
			break
		}
	}
	for i := 0; i < len(line2); i++ {
		if line2[i] == '\r' || line2[i] == '\n' {
			line2 = line2[:i]
			break
		}
	}

	fmt.Println(editDistance(line1, line2))
}
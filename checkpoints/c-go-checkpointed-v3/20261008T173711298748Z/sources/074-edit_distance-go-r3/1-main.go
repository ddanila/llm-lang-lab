package main

import (
	"fmt"
	"strings"
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

	// Initialize base cases
	for i := 0; i <= n; i++ {
		dp[i][0] = i
	}
	for j := 0; j <= m; j++ {
		dp[0][j] = j
	}

	// Fill the table
	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				insertion := dp[i][j-1]
				deletion := dp[i-1][j]
				substitution := dp[i-1][j-1]
				dp[i][j] = 1 + insertion
				if deletion < dp[i][j] {
					dp[i][j] = 1 + deletion
				}
				if substitution < dp[i][j] {
					dp[i][j] = 1 + substitution
				}
			}
		}
	}

	return dp[n][m]
}

func main() {
	input := strings.SplitN(readLine(), "\n", -1)
	if len(input) < 2 {
		fmt.Println(0)
		return
	}
	s1 := input[0]
	s2 := readLine()
	if s2 == "" && !strings.HasSuffix(input[len(input)-1], "") {
		s2 = ""
	} else if len(input) >= 2 {
		s2 = input[1]
	}

	fmt.Println(editDistance(s1, s2))
}

func readLine() string {
	var buf [80]byte
	n := 0
	for i := range buf {
		c := rune(buf[i])
		if c == '\n' || c == '\r' {
			return string(buf[:i])
		}
		buf[i] = c
		n++
	}
	return string(buf)
}
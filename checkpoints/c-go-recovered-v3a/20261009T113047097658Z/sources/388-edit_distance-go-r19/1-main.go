package main

import (
	"bufio"
	"fmt"
	"os"
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
				dp[i][j] = min(
					dp[i-1][j]+1,    // deletion
					dp[i][j-1]+1,    // insertion
					dp[i-1][j-1]+1,  // substitution
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
	reader := bufio.NewReader(os.Stdin)
	line1, err := reader.ReadString('\n')
	if err != nil {
		os.Exit(1)
	}
	line2, err := reader.ReadString('\n')
	if err != nil {
		os.Exit(1)
	}

	s1 := line1[:len(line1)-1] // remove newline
	s2 := line2[:len(line2)-1] // remove newline

	fmt.Println(editDistance(s1, s2))
}
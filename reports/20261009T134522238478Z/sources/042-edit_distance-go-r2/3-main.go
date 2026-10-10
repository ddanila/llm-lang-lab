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
				dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
			}
		}
	}

	return dp[n][m]
}

func min(a, b, c int) int {
	if a <= b {
		a = b
	}
	if a <= c {
		a = c
	}
	return a
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	line1, err := reader.ReadString('\n')
	if err != nil && err.Error() != "EOF" {
		os.Exit(1)
	}
	if len(line1) > 0 && line1[len(line1)-1] == '\n' {
		line1 = line1[:len(line1)-1]
	}

	line2, err := reader.ReadString('\n')
	if err != nil {
		os.Exit(1)
	}
	if len(line2) > 0 && line2[len(line2)-1] == '\n' {
		line2 = line2[:len(line2)-1]
	}

	result := editDistance(line1, line2)
	fmt.Println(result)
}
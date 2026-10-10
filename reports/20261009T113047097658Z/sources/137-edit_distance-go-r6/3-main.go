package main

import (
	"bufio"
	"fmt"
	"os"
)

func editDistance(s1, s2 string) int {
	m, n := len(s1), len(s2)
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
			cost := 0
			if s1[i-1] != s2[j-1] {
				cost = 1
			}
			dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1]+cost)
		}
	}

	return dp[m][n]
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
	line1, err1 := reader.ReadString('\n')
	if err1 != nil {
		fmt.Println(0)
		return
	}
	line2, err2 := reader.ReadString('\n')
	if err2 != nil {
		fmt.Println(len(line1))
		return
	}

	s1 := line1[:len(line1)-1]
	s2 := line2[:len(line2)-1]

	dist := editDistance(s1, s2)
	fmt.Println(dist)
}
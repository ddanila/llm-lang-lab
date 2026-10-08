package main

import (
	"bufio"
	"fmt"
	"os"
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
				insertion := dp[i][j-1]
				deletion := dp[i-1][j]
				substitution := dp[i-1][j-1]
				if 1+insertion < dp[i][j] {
					dp[i][j] = 1 + insertion
				}
				if 1+deletion < dp[i][j] {
					dp[i][j] = 1 + deletion
				}
				if 1+substitution < dp[i][j] {
					dp[i][j] = 1 + substitution
				}
			}
		}
	}

	return dp[n][m]
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	line1, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println(0)
		return
	}

	s1 := strings.TrimRight(line1, "\r\n")

	line2, err := reader.ReadString('\n')
	if err != nil {
		s2 := ""
		result := editDistance(s1, s2)
		fmt.Println(result)
		return
	}

	s2 := strings.TrimRight(line2, "\r\n")

	result := editDistance(s1, s2)
	fmt.Println(result)
}
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
		c1 := s1[i-1]
		for j := 1; j <= m; j++ {
			c2 := s2[j-1]
			if c1 == c2 {
				dp[i][j] = dp[i-1][j-1]
			} else {
				v1 := dp[i-1][j]
				v2 := dp[i][j-1]
				v3 := dp[i-1][j-1]
				if v1 <= v2 {
					a := v1
				} else {
					a := v2
				}
				if a <= v3 {
					dp[i][j] = 1 + a
				} else {
					dp[i][j] = 1 + v3
				}
			}
		}
	}

	return dp[n][m]
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	line1, err1 := reader.ReadString('\n')
	if err1 != nil && err1.Error() == "EOF" {
		os.Exit(0)
	}
	if len(line1) > 0 && line1[len(line1)-1] == '\n' {
		line1 = line1[:len(line1)-1]
	}

	line2, err2 := reader.ReadString('\n')
	if err2 != nil {
		os.Exit(0)
	}
	if len(line2) > 0 && line2[len(line2)-1] == '\n' {
		line2 = line2[:len(line2)-1]
	}

	result := editDistance(line1, line2)
	fmt.Println(result)
}
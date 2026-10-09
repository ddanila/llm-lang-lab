package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func editDistance(s1, s2 string) int {
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
				cost := dp[i-1][j-1] + 1
				insertCost := dp[i][j-1] + 1
				delCost := dp[i-1][j] + 1
				if cost < insertCost && cost < delCost {
					dp[i][j] = cost
				} else if insertCost < delCost {
					dp[i][j] = insertCost
				} else {
					dp[i][j] = delCost
				}
			}
		}
	}

	return dp[n][m]
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	line1, err := reader.ReadString('\n')
	if err != nil || len(line1) == 0 {
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
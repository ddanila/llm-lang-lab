package main

import "fmt"

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
	for i := 0; i <= n; i++ {
		dp[i] = make([]int, m+1)
	}

	// Initialize first row and column
	for i := 0; i <= n; i++ {
		dp[i][0] = i
	}
	for j := 0; j <= m; j++ {
		dp[0][j] = j
	}

	// Fill the DP table
	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				insertion := dp[i][j-1]
				deletion := dp[i-1][j]
				substitution := dp[i-1][j-1] + 1

				if insertion <= deletion && insertion <= substitution {
					dp[i][j] = insertion
				} else if deletion <= substitution {
					dp[i][j] = deletion
				} else {
					dp[i][j] = substitution
				}
			}
		}
	}

	return dp[n][m]
}

func main() {
	var line string
	fmt.Scanln(&line)
	s1 := line

	fmt.Scanln(&line)
	s2 := line

	fmt.Println(editDistance(s1, s2))
}
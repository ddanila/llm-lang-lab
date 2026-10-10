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

	// Use a single row for space optimization, but keep full matrix for clarity
	dp := make([]int, m+1)

	for j := 0; j <= m; j++ {
		dp[j] = j
	}

	for i := 1; i <= n; i++ {
		prevDiag := dp[0]
		dp[0] = i

		for j := 1; j <= m; j++ {
			old := dp[j]
			if s1[i-1] == s2[j-1] {
				dp[j] = prevDiag
			} else {
				dp[j] = min(prevDiag+1, min(dp[j]+1, old+1))
			}
			prevDiag = old
		}
	}

	return dp[m]
}

func min(a, b, c int) int {
	if a <= b && a <= c {
		return a
	}
	if b <= a && b <= c {
		return b
	}
	return c
}

func main() {
	reader := bufio.NewReader(nil)
	
	var s1, s2 string
	
	// Read first line
	line1, err1 := reader.ReadString('\n')
	if err1 != nil && err1 != bufio.ErrNoMoreInput {
		return
	}
	s1 = line1[:len(line1)-1] // Remove newline
	
	// Read second line
	line2, err2 := reader.ReadString('\n')
	if err2 != nil && err2 != bufio.ErrNoMoreInput {
		return
	}
	s2 = line2[:len(line2)-1] // Remove newline

	dist := editDistance(s1, s2)
	fmt.Println(dist)
}
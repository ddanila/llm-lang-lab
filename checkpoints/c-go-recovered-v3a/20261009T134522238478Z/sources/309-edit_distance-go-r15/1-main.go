package main

import (
	"fmt"
	"strings"
)

func main() {
	lines := strings.SplitN(readAll(), "\n", 2)
	if len(lines) == 1 {
		s1 := lines[0]
		fmt.Println(editDistance(s1, ""))
		return
	}
	s1 := lines[0]
	s2 := lines[1]
	fmt.Println(editDistance(s1, s2))
}

func readAll() string {
	buf := make([]byte, 0, 80)
	for {
		n, err := read(buf[len(buf):])
		if n > 0 {
			buf = append(buf[:len(buf)-n], buf[n:])
		}
		if err != nil || n == 0 {
			break
		}
	}
	return string(buf)
}

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
				dp[i][j] = min(
					dp[i-1][j]+1,      // deletion
					dp[i][j-1]+1,      // insertion
					dp[i-1][j-1]+1,    // substitution
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
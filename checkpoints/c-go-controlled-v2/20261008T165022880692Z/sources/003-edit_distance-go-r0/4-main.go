package main

import (
	"bufio"
	"fmt"
	"os"
)

func levenshtein(s1, s2 string) int {
	n, m := len(s1), len(s2)
	if n == 0 {
		return m
	}
	if m == 0 {
		return n
	}
	
	// Use two rows to save space
	prev := make([]int, m+1)
	curr := make([]int, m+1)
	
	for j := 0; j <= m; j++ {
		prev[j] = j
	}
	
	for i := 1; i <= n; i++ {
		curr[0] = i
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				curr[j] = prev[j-1]
			} else {
				curr[j] = 1 + min(prev[j], curr[j-1], prev[j-1])
			}
		}
		copy(prev, curr)
	}
	
	return prev[m]
}

func min(a, b, c int) int {
	if a < b {
		a = b
	}
	if a < c {
		a = c
	}
	return a
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	
	var line1, line2 string
	
	if scanner.Scan() {
		line1 = scanner.Text()
	}
	
	if scanner.Scan() {
		line2 = scanner.Text()
	}
	
	result := levenshtein(line1, line2)
	fmt.Println(result)
}
package main

import (
	"fmt"
)

func main() {
	var line1, line2 string
	
	// Read first line
	_, err1 := fmt.Scanln(&line1)
	if err1 != nil {
		return
	}
	
	// Read second line
	_, err2 := fmt.Scanln(&line2)
	if err2 != nil {
		return
	}

	s1 := line1
	s2 := line2

	n := len(s1)
	m := len(s2)

	if n == 0 && m == 0 {
		fmt.Println(0)
		return
	}
	
	prev := make([]int, m+1)
	curr := make([]int, m+1)

	for j := 0; j <= m; j++ {
		prev[j] = j
	}

	for i := 1; i <= n; i++ {
		curr[0] = i
		for j := 1; j <= m; j++ {
			if s1[i-1] == s2[j-1] {
				curr[j] = prev[j]
			} else {
				curr[j] = min(prev[j]+1, curr[j-1]+1, prev[j-1]+1)
			}
		}
		copy(prev, curr)
	}

	fmt.Println(prev[m])
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
package main

import (
	"bufio"
	"fmt"
	"os"
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

	// Use two rows to save space
	prev := make([]int, m+1)
	curr := make([]int, m+1)

	for i := 0; i <= n; i++ {
		for j := 0; j <= m; j++ {
			if i == 0 {
				prev[j] = j
			} else if j == 0 {
				curr[j] = i
			} else if s1[i-1] == s2[j-1] {
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
	if a <= b && a <= c {
		return a
	}
	if b <= a && b <= c {
		return b
	}
	return c
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	line1, err := reader.ReadString('\n')
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	line2, err := reader.ReadString('\n')
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	s1 := line1[:len(line1)-1]
	s2 := line2[:len(line2)-1]

	dist := editDistance(s1, s2)
	fmt.Println(dist)
}
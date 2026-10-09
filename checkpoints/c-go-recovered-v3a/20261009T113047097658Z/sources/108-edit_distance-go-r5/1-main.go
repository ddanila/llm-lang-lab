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

	prev := make([]int, m+1)
	curr := make([]int, m+1)

	for j := 0; j <= m; j++ {
		prev[j] = j
	}

	for i := 1; i <= n; i++ {
		curr[0] = i
		for j := 1; j <= m; j++ {
			cost := 0
			if s1[i-1] != s2[j-1] {
				cost = 1
			}
			curr[j] = min(prev[j]+1, curr[j-1]+1, prev[j-1]+cost)
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

	line1, err1 := reader.ReadString('\n')
	if err1 != nil {
		os.Exit(1)
	}
	line1 = line1[:len(line1)-1]

	line2, err2 := reader.ReadString('\n')
	if err2 != nil {
		os.Exit(1)
	}
	line2 = line2[:len(line2)-1]

	result := editDistance(line1, line2)
	fmt.Println(result)
}
package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	line1, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println(0)
		return
	}
	line1 = line1[:len(line1)-1] // Remove newline

	line2, err := reader.ReadString('\n')
	if err != nil {
		fmt.Println(0)
		return
	}
	line2 = line2[:len(line2)-1] // Remove newline

	distance := editDistance(line1, line2)
	fmt.Println(distance)
}

func editDistance(s1, s2 string) int {
	m, n := len(s1), len(s2)

	if m == 0 {
		return n
	}
	if n == 0 {
		return m
	}

	// Use two rows to save space
	prev := make([]int, n+1)
	curr := make([]int, n+1)

	for j := 0; j <= n; j++ {
		prev[j] = j
	}

	for i := 1; i <= m; i++ {
		curr[0] = i
		for j := 1; j <= n; j++ {
			if s1[i-1] == s2[j-1] {
				curr[j] = prev[j-1]
			} else {
				insertion := curr[j-1] + 1
				deletion := prev[j] + 1
				substitution := prev[j-1] + 1

				if insertion < deletion && insertion < substitution {
					curr[j] = insertion
				} else if deletion < substitution {
					curr[j] = deletion
				} else {
					curr[j] = substitution
				}
			}
		}
		copy(prev, curr)
	}

	return prev[n]
}
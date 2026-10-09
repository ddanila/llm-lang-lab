package main

import (
	"fmt"
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

	// Use two rows to save space
	prev := make([]int, m+1)
	curr := make([]int, m+1)

	// Initialize first row (empty s1)
	for j := 0; j <= m; j++ {
		prev[j] = j
	}

	// Fill the DP table
	for i := 0; i < n; i++ {
		curr[0] = i + 1 // First column (empty s2)
		for j := 0; j < m; j++ {
			if s1[i] == s2[j] {
				curr[j+1] = prev[j]
			} else {
				insertion := curr[j]
				deletion := prev[j+1]
				substitution := prev[j] + 1

				if insertion <= deletion && insertion <= substitution {
					curr[j+1] = insertion
				} else if deletion <= substitution {
					curr[j+1] = deletion
				} else {
					curr[j+1] = substitution
				}
			}
		}
		// Swap rows
		prev, curr = curr, prev
	}

	return prev[m]
}

func main() {
	s1 := ""
	s2 := ""

	fmt.Fscanln(&in) := func(in *[]byte) int { return 0 } // placeholder to avoid unused var error
	var in string
	fmt.Scanln(&in)
	s1 = in
	if s1 == "" {
		fmt.Fscanf(os.Stdin, "%s", &in)
	}

	// Simpler approach using os.Stdin directly
	in := make([]byte, 0, 82)
	for i := 0; i < 2; i++ {
		line := ""
		_, err := fmt.Scanln(&line)
		if err == nil {
			s1 = line
		} else if i == 0 {
			s2 = ""
		}
	}

	fmt.Println(editDistance(s1, s2))
}